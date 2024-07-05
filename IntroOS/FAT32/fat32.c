#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>
#include "fat32.h"

struct Fat32BPB *hdr; 
int mounted = -1;     

#define MAX_OPEN_FILES 128

typedef struct
{
    int is_open;      
    int size;          // 文件大小
    int start_cluster; // 文件起始簇
    int offset;        // 当前文件偏移量
    char path[256];    // 文件路径
} OpenFile;

OpenFile open_files[MAX_OPEN_FILES]; 
int open_file_count = 0;            



// 路径转换为目录项名称格式
void path_to_dirname(const char *path, char *dirname)
{
    memset(dirname, ' ', 11);
    const char *dot = strrchr(path, '.');
    int name_len = dot ? dot - path : strlen(path);
    int ext_len = dot ? strlen(dot + 1) : 0;

    int copy_len = name_len > 8 ? 8 : name_len;
    memcpy(dirname, path, copy_len);
    
    if (dot)
    {
        int ext_copy_len = ext_len > 3 ? 3 : ext_len;
        memcpy(dirname + 8, dot + 1, ext_copy_len);
    }

    for (int i = 0; i < 11; i++)
    {
        if (dirname[i] >= 'a' && dirname[i] <= 'z')
        {
            dirname[i] -= 32;
        }
    }
}

// 读取簇数据
int read_cluster(int cluster, void *buffer, int cluster_size)
{

    int data_start = (hdr->BPB_RsvdSecCnt + hdr->BPB_NumFATs * hdr->BPB_FATSz32) * hdr->BPB_BytsPerSec;
    int cluster_offset = data_start + (cluster - 2) * cluster_size;
    memcpy(buffer, (char *)hdr + cluster_offset, cluster_size);
    return cluster_size;
}


// 获取下一个簇号
int get_next_cluster(int cluster) {
    // 计算FAT表中对应簇号的偏移量
    int fatOffset = cluster * 4;
    // 计算FAT表所在扇区号
    int fatSector = hdr->BPB_RsvdSecCnt + (fatOffset / hdr->BPB_BytsPerSec);
    // 计算在扇区内的偏移量
    int entOffset = fatOffset % hdr->BPB_BytsPerSec;

    // 获取FAT表的指针
    uint32_t *fat = (uint32_t *)((char *)hdr + fatSector * hdr->BPB_BytsPerSec);
    // 返回下一个簇号
    return fat[entOffset / 4] & 0x0FFFFFFF;
}


// 挂载磁盘镜像
int fat_mount(const char *path)
{

    int fd = open(path, O_RDWR);
    if (fd < 0)
    {
        // 打开失败
        return -1;
    }
   
    off_t size = lseek(fd, 0, SEEK_END);
    if (size == -1)
    {
        return -1;
    }
    // 将磁盘镜像映射到内存
    hdr = (struct Fat32BPB *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (hdr == (void *)-1)
    {
        return -1;
    }
    // 关闭文件
    close(fd);

    assert(hdr->Signature_word == 0xaa55);                  
    assert(hdr->BPB_TotSec32 * hdr->BPB_BytsPerSec == size); 

    // 打印 BPB 的部分信息
    printf("Some of the information about BPB is as follows\n");
    printf("OEM-ID \"%s\", \n", hdr->BS_oemName);
    printf("sectors/cluster %d, \n", hdr->BPB_SecPerClus);
    printf("bytes/sector %d, \n", hdr->BPB_BytsPerSec);
    printf("sectors %d, \n", hdr->BPB_TotSec32);
    printf("sectors/FAT %d, \n", hdr->BPB_FATSz32);
    printf("FATs %d, \n", hdr->BPB_NumFATs);
    printf("reserved sectors %d, \n", hdr->BPB_RsvdSecCnt);

    // 挂载成功
    mounted = 0;
    return 0;
}


// 查找文件，返回起始簇和文件大小，并判断是否是目录文件
int find_file(const char *path, int *start_cluster, int *file_size, int *is_directory)
{

    int cluster = hdr->BPB_RootClus;
    int cluster_size = hdr->BPB_BytsPerSec * hdr->BPB_SecPerClus;
    char buffer[cluster_size];

    if (path[0] != '/')
        return -1;
    *is_directory = 1;
    char path_copy[256];
    strcpy(path_copy, path);
    char *token = strtok(path_copy, "/");

    while (token != NULL)
    {
        read_cluster(cluster, buffer, cluster_size);
        struct DirEntry *dir = (struct DirEntry *)buffer;
        char dirname[11];
        path_to_dirname(token, dirname);

        int found = 0;
        for (int i = 0; i < cluster_size / sizeof(struct DirEntry); i++)
        {
            if (memcmp(dir[i].DIR_Name, dirname, 11) == 0)
            {
                cluster = (dir[i].DIR_FstClusHI << 16) | dir[i].DIR_FstClusLO;
                *file_size = dir[i].DIR_FileSize;
                *is_directory = (dir[i].DIR_Attr & DIRECTORY) != 0;
                found = 1;
                break;
            }
        }

        if (!found)
        {
            return -1;
        }

        token = strtok(NULL, "/");
    }

    *start_cluster = cluster;
    return 0;
}
// 打开文件
int fat_open(const char *path)
{
    if (mounted != 0 || open_file_count >= MAX_OPEN_FILES) {
        return -1;
    }

    int file_size, start_cluster, is_directory;
    if (find_file(path, &start_cluster, &file_size, &is_directory) != 0)
    {
        return -1;
    }

    if (is_directory)
    {
        return -1;
    }
    // 找到空闲文件描述符并分配文件结构
    for (int i = 0; i < MAX_OPEN_FILES; i++) {
        if (!open_files[i].is_open) {
            strcpy(open_files[i].path, path);
            open_files[i].is_open = 1;
            open_files[i].size = file_size;
            open_files[i].start_cluster = start_cluster;
            open_files[i].offset = 0;
            open_file_count++;
            return i;
        }
    }

    return -1;
}
// 关闭文件
int fat_close(int fd)
{
    if (fd < 0 || fd >= MAX_OPEN_FILES || !open_files[fd].is_open)
    {
        return -1;
    }

    open_files[fd].is_open = 0;
    open_file_count--;
    return 0;
}

// 读取文件内容
int fat_pread(int fd, void *buffer, int count, int offset)
{
    if (fd < 0 || fd >= MAX_OPEN_FILES || !open_files[fd].is_open)
    {
        return -1;
    }

    OpenFile *file = &open_files[fd];

    if (count == 0 || offset >= file->size)
    {
        return 0;
    }

    if (offset + count > file->size)
    {
        count = file->size - offset;
    }

    int cluster_size = hdr->BPB_BytsPerSec * hdr->BPB_SecPerClus;
    int cluster = file->start_cluster + (offset / cluster_size);
    int cluster_offset = offset % cluster_size;
    int bytes_read = 0;

    while (count > 0)
    {
        int to_read = cluster_size - cluster_offset;
        if (to_read > count)
        {
            to_read = count;
        }
        if (to_read < 0)
            break;

        // 定义一个缓冲区来存储当前簇的数据
        char cluster_buffer[cluster_size];
        if (read_cluster(cluster, cluster_buffer, cluster_size) != cluster_size)
        {
            return -1;
        }
        
        memcpy(buffer, cluster_buffer + cluster_offset, to_read);
        buffer = (char *)buffer + to_read;
        bytes_read += to_read;
        count -= to_read;
        cluster++;
        cluster_offset = 0;
    }

    return bytes_read;
}

// 读取目录文件内容 (目录项)
struct FilesInfo *fat_readdir(const char *path)
{
    int file_size;
    int start_cluster;
    int is_directory;
    if (mounted != 0 || find_file(path, &start_cluster, &file_size, &is_directory) != 0 || !is_directory)
    {
        return NULL;
    }



    // 计算簇的大小
    int cluster_size = hdr->BPB_BytsPerSec * hdr->BPB_SecPerClus;
    char buffer[cluster_size];
    read_cluster(start_cluster, buffer, cluster_size);
    struct DirEntry *dir = (struct DirEntry *)buffer;
    struct FilesInfo *files_info = (struct FilesInfo *)malloc(sizeof(struct FilesInfo));
    files_info->files = (struct FileInfo *)malloc(cluster_size / sizeof(struct DirEntry) * sizeof(struct FileInfo));
    files_info->size = 0;

    for (int i = 0; i < cluster_size / sizeof(struct DirEntry); i++)
    {
        if (dir[i].DIR_Name[0] == 0xE5 || dir[i].DIR_Name[0] == 0x00)
        {
            continue;
        }
        if ((dir[i].DIR_Attr & DIRECTORY) && (dir[i].DIR_Name[0] == '.') &&
            (dir[i].DIR_Name[1] == ' ' || dir[i].DIR_Name[1] == '.' && dir[i].DIR_Name[2] == ' '))
        {
            continue;
        }

        // 解析文件名
        char filename[13]; 
        int j = 0;
        int k = 0;
        while (j < 8 && dir[i].DIR_Name[j] != ' ')
        {
            filename[k++] = dir[i].DIR_Name[j++];
        }
        if (dir[i].DIR_Name[8] != ' ')
        {
            filename[k++] = '.';
            j = 8;
            while (j < 11 && dir[i].DIR_Name[j] != ' ')
            {
                filename[k++] = dir[i].DIR_Name[j++];
            }
        }
        filename[k] = '\0';

        strcpy((char *)files_info->files[files_info->size].DIR_Name, filename);
        files_info->files[files_info->size].DIR_FileSize = dir[i].DIR_FileSize;
        files_info->size++;
    }

    return files_info;
}
