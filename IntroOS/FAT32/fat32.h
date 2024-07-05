#ifndef FAT_H_
#define FAT_H_

#include <stdint.h>

// FAT32 文件系统中 BPB 的各个数据，具体含义请参照 FAT 规范
struct Fat32BPB {
    uint8_t BS_jmpBoot[3];
    uint8_t BS_oemName[8];
    uint16_t BPB_BytsPerSec;
    uint8_t BPB_SecPerClus;
    uint16_t BPB_RsvdSecCnt;
    uint8_t BPB_NumFATs;
    uint16_t BPB_rootEntCnt;
    uint16_t BPB_totSec16;
    uint8_t BPB_media;
    uint16_t BPB_FATSz16;
    uint16_t BPB_SecPerTrk;
    uint16_t BPB_NumHeads;
    uint32_t BPB_HiddSec;
    uint32_t BPB_TotSec32;
    uint32_t BPB_FATSz32;
    uint16_t BPB_ExtFlags;
    uint16_t BPB_FSVer;
    uint32_t BPB_RootClus;
    uint16_t BPB_FSInfo;
    uint16_t BPB_bkBootSec;
    uint8_t BPB_reserved[12];
    uint8_t BS_DrvNum;
    uint8_t BS_Reserved1;
    uint8_t BS_BootSig;
    uint32_t BS_VolID;
    uint8_t BS_VolLab[11];
    uint8_t BS_FileSysTye[8];
    uint8_t  __padding_1[420];
    uint16_t Signature_word;
} __attribute__((packed));

// 目录项 (短文件名)
struct DirEntry {
    uint8_t DIR_Name[11];
    uint8_t DIR_Attr;
    uint8_t DIR_NTRes;
    uint8_t DIR_CrtTimeTenth;
    uint16_t DIR_CrtTime;
    uint16_t DIR_CrtDate;
    uint16_t DIR_LstAccDate;
    uint16_t DIR_FstClusHI;
    uint16_t DIR_WrtTime;
    uint16_t DIR_WrtDate;
    uint16_t DIR_FstClusLO;
    uint32_t DIR_FileSize;
} __attribute__((packed));

// 目录项的属性，即 DIR_Attr 字段
enum DirEntryAttributes {
    READ_ONLY       = 0x01,
    HIDDEN          = 0x02,
    SYSTEM          = 0x04,
    VOLUME_ID       = 0x08,
    DIRECTORY       = 0x10,
    ARCHIVE         = 0x20,
    LONG_NAME       = 0x0F,
    LONG_NAME_MASK  = 0x3F,
};

// 用于存储文件名及文件大小
struct FileInfo {
    uint8_t DIR_Name[11];
    uint32_t DIR_FileSize;
};

// 用于存储一个目录文件中包含的所有文件的文件名及文件大小
struct FilesInfo {
    struct FileInfo *files;
    int size;
};

// 你应当在 fat.c 中实现以下函数 (fat_mount 已实现)
extern int fat_mount(const char *path);
extern int fat_open(const char *path);
extern int fat_close(int fd);
extern int fat_pread(int fd, void *buffer, int count, int offset);
extern struct FilesInfo* fat_readdir(const char *path);

#endif
