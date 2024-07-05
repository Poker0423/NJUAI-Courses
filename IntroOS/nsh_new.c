#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <pwd.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>




char error_message[28] = "An error has occurred\n";
static char PATH[114514];
static int path_count;
static char f[]="fucking";
typedef struct {
  int pid;
  char cmd[1024];
} BG_task;
BG_task bg_tasks[20];
int bg_task_count = 0;

bool judge_spaces(char *str)
{
  size_t len=strlen(str);
  for(int i=0;i<len;++i)
  {
    if(isspace(str[i])) continue;
    else return 0;
  }
  return 1;
}


char* trim(char* str) {
    char* end;
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)  
        return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    *(end+1) = 0;
    return str;
}

bool is_token(char c)
{
  if((c=='&')||(c==';')||(c=='|')||(c=='>')) return 1;
  else return 0;
}

bool judge_neighbor(char buf[],int index) 
{
  if(is_token(buf[index])&&is_token(buf[index+1])) return 1;
  else return 0;
}

bool judge_near_neighbor(char buf[],int index,int len)
{
  if(!is_token(buf[index])) return 0;
  index++;
  while(index<len)
  {
    if(isspace(buf[index++])) continue;
    else 
    { 
      if(is_token(buf[index-1])&&buf[index-1]!='>') return 1;
      else return 0;
    }
  }
  return 0;
}


#define MAX_BG_TASKS 20
void add_bg_task(int pid,char* cmd)
{
  if(bg_task_count>=MAX_BG_TASKS) {printf("Too many bg_tasks.\n");return;}
  else
  {
    bg_tasks[bg_task_count].pid=pid;
    strcpy(bg_tasks[bg_task_count].cmd,cmd);  
    bg_tasks[bg_task_count].cmd[strlen(cmd)]='\0';  
    bg_task_count++; 
    printf("Process %d %s: running in background\n", pid, cmd);
    fflush(stdout);
  }
  fflush(stdout);
}

void remove_bg_task(int pid)
{
  for(int i=0;i<bg_task_count;i++) 
  {  
    if(bg_tasks[i].pid==pid) 
    {  
      for(int j=i;j<bg_task_count-1;j++) 
      {  
        bg_tasks[j].pid=bg_tasks[j+1].pid;
        strcpy(bg_tasks[j].cmd,bg_tasks[j+1].cmd);  
      }  
      bg_task_count--;  
      return;  
    }  
  }
}


#define MAX_HISTORY 100
char *history[MAX_HISTORY];
int history_count = 0;

void add_history(char *cmd) {
    if (history_count < MAX_HISTORY) {
        history[history_count++] = strdup(cmd);  
    } else {
        free(history[0]);  
        for (int i = 1; i < MAX_HISTORY; i++) {
            history[i - 1] = history[i];
        }
        history[MAX_HISTORY - 1] = strdup(cmd);
    }
}

void print_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d %s\n", i + 1, history[i]);
        fflush(stdout);
    }
}

void free_history() {
    for (int i = 0; i < history_count; i++) {
        free(history[i]);
    }
}


bool handle_cd(int argc,char* argv[],bool output)
{
  if(output) return 1;
  if(argc!=2) {printf("%s",error_message);
  fflush(stdout);
  return 1;}
  if(strcmp(argv[1],"~")==0) {
  struct passwd *pw;  
  const char *homedir;  
  pw = getpwuid(getuid());  
  if(pw==NULL) 
  {  
     perror("getpwuid");  
     return 1;  
  }  
  homedir = pw->pw_dir;  
  if(homedir==NULL) 
  {  
     perror("pw_dir");  
     return 1;  
  }   
  if(chdir(homedir)!= 0)
  {  
     perror("chdir");  
     return 1;  
  }
  return 1;}
  else
  {
    if(!chdir(argv[1])) return 1;
    printf("%s",error_message);
    fflush(stdout);
  }
  fflush(stdout);
  return 1;
}

bool handle_path(int argc,char* argv[],bool output)
{
  if(argc==1)
  { 
    if(!output) return 1;
    char* buf = (char*)malloc(strlen(PATH)*sizeof(char));
    memset(buf,0,strlen(PATH));
    strcpy(buf,PATH);
    char *s = (char*)malloc(sizeof(char)*200);
    memset(s,0,200);
    s = strtok(buf,":");
    int cnt = 0;
    while(1)
    {
      printf("%d\t%s\n", cnt+1, s);
      fflush(stdout);
      cnt++;
      s = strtok(NULL,":");
      if(s==NULL) break;
    }
    free(buf);
    free(s);
  }
  else
  {
    path_count=argc-1;
    int count=0;
    memset(PATH,0,strlen(PATH));
    for(int i=1;i<argc;i++)
    {
      strcpy(PATH+count,argv[i]);
      PATH[strlen(PATH)] = ':';
      count += strlen(PATH);
    }
  }
  fflush(stdout);
  return 1;
}

bool handle_bg(int argc,char* argv[],bool output)

{
  if(argc!=1) {printf("%s",error_message);fflush(stdout); return 1;}
  if(output)
  { 
    for(int i=0;i<bg_task_count;i++)
    {
      printf("%d\t%d\t%s\n",i+1,bg_tasks[i].pid,bg_tasks[i].cmd);
      fflush(stdout);
    }
  }
  fflush(stdout);
  return 1;
}

bool handle_builtin_commands(char* args[],int cnt,bool output)
{
  bool judge=0;
  if(strcmp(args[0],"exit")==0) exit(0);
  else if(strcmp(args[0],"cd")==0) judge = judge | handle_cd(cnt,args,output);
  else if(strcmp(args[0],"paths")==0) judge = judge | handle_path(cnt,args,output);
  else if(strcmp(args[0],"bg")==0) judge = judge | handle_bg(cnt,args,output);
  else if(strcmp(args[0],"fucking")==0&&cnt==1) judge = 1;
  return judge;
}

void execute(char* args[],int cnt)
{
  bool judge=0;
  char* buf = (char*)malloc(strlen(PATH)*sizeof(char));
  memset(buf,0,strlen(PATH));
  strcpy(buf,PATH);
    char *s = (char*)malloc(sizeof(char)*200);
    s = strtok(buf,":");
    while(1)
    {
      close(STDERR_FILENO);
      char* szcmd = malloc(sizeof(char)*(2+strlen(s)+strlen(args[0])));
      strcpy(szcmd,s);
      strcat(szcmd,"/");
      strcat(szcmd,args[0]);
      if(execv(szcmd,args)!=-1) judge=1;
      s = strtok(NULL,":");
      if(s==NULL) break;
    }

    free(buf);
    free(s);
    fflush(stdout);
    exit(-1);
}

#define MSGSIZE 108
void handle_pipe(char* pipe_args[],int pipe_num,bool is_grandpa,char* filename,bool if_after) 
{
  if(!is_grandpa){
  int stdout_orig,stderr_orig;
  if(filename!=NULL)
  {
    int fd = open(filename, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU);
    if(fd==-1) 
    {
      printf("error opening file\n");
      return;
    }
    stdout_orig = dup(STDOUT_FILENO);  
    stderr_orig = dup(STDERR_FILENO);
    if(stdout_orig==-1) {  
      printf("Error duplicating stdout\n");  
      close(fd);  
      return;  
    }
    if(stderr_orig==-1) {  
      printf("Error duplicating stderr\n");  
      close(fd);  
      return;  
    }
    if(dup2(fd, STDOUT_FILENO) == -1) {  
      printf("Error redirecting stdout");  
      close(fd);  
      close(stdout_orig);  
      return;  
    }  
    if(dup2(fd, STDERR_FILENO) == -1) {  
      printf("Error redirecting stderr");  
      close(fd);  
      close(stderr_orig);  
      return;  
    }
    close(fd);
  }
  bool judge_error = 0;
  for(int i=0;i<pipe_num;i++)
  {
    int fd[2];
    if(pipe(&fd[0])<0)
    {
      printf("pipe call error!\n");
      return;
    }
    else
    {
      char* args[114];
      args[0]=strtok(pipe_args[i]," ");
      int cnt=0;
      if(args[0]!=NULL)
      {
        while(1)
        {
          args[++cnt] = strtok(NULL," ");
          if(args[cnt]==NULL) break;
        }
      }
      int pid=fork();
      if(pid<0)
      {
        printf("An error has occurred\n");
        return;
      }
      else if(pid>0) 
      {
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        close(fd[0]);
       
        int status;
        waitpid(pid,&status,0);
        if(WEXITSTATUS(status)!=0) judge_error = 1;
        if(judge_error&&i==pipe_num-1&&(!if_after||(if_after&&pipe_num!=1))) {printf("%s",error_message);fflush(stdout); }
      } 
      else 
      {
        close(fd[0]);
        if(i!=pipe_num-1) dup2(fd[1],STDOUT_FILENO);
        close(fd[1]);
        bool jud=0;
        if(args[0]!=NULL)
        {
          jud = handle_builtin_commands(args,cnt,1);
          if(i==0&&if_after) exit(0);
          if(jud) { exit(0);}
          execute(args,cnt);
        }
        exit(0);
      }
    }
  }
  if(filename!=NULL)
  {
    dup2(stdout_orig, STDOUT_FILENO);  
    close(stdout_orig);
    dup2(stderr_orig, STDERR_FILENO);
    close(stderr_orig);
  }
  }
  else
  {
    for(int i=0;i<pipe_num;i++)
    {
      char* args[114];
      args[0]=strtok(pipe_args[i]," ");
      if(args[0]==NULL) {printf("%s",error_message); 
      fflush(stdout);
      return;}
      int cnt=0;
      while(1)
      {
        args[++cnt] = strtok(NULL," ");
        if(args[cnt]==NULL) break;
      }
      if(pipe_num==1) {handle_builtin_commands(args,cnt,0);}
      else break;
    }
  }
  fflush(stdout);
}

void execute_once(char* cmd_args)
{
    int re_num = 0;
    char* filepath=NULL;
    for(int j=0;j<strlen(cmd_args);j++)
    {
      if(cmd_args[j]=='>') re_num++;
    }
    if(re_num>1) {printf("%s",error_message);fflush(stdout);return;}
    else if(re_num==1)
    {
      char* re_args[2];
      if(cmd_args[0]=='>') {re_args[0]=NULL;re_args[1] = strtok(cmd_args,">");} 
      else
      {
        re_args[0] = strtok(cmd_args,">");
        re_args[1] = strtok(NULL,">");
      }
      if(re_args[1]==NULL) {printf("%s",error_message);fflush(stdout);return;}


      int after_pipe_num = 0;
      int t_after_pipe_count=0;
      for(int i=0;i<strlen(re_args[1]);i++)
      { 
        if(re_args[1][i]=='|') t_after_pipe_count++;
      }
      char* after_pipe_args[114];
      char* file_args[2];
      file_args[0]=strtok(re_args[1],"|");
      after_pipe_args[0]=f;
      while(1)
      {
        after_pipe_args[++after_pipe_num] = strtok(NULL,"|");
        if(after_pipe_args[after_pipe_num]==NULL) break;
      }
      filepath = strtok(file_args[0]," ");
      file_args[1] = strtok(NULL,"");
      if(after_pipe_num!=t_after_pipe_count+1) {
      printf("%s",error_message);
      fflush(stdout);
      return;
   }

      int pipe_num = 0;
      int t_pipe_count=0;
      if(re_args[0]!=NULL)
      {
        for(int i=0;i<strlen(re_args[0]);i++)
        {
          if(re_args[0][i]=='|') t_pipe_count++;
        }
      }
      char* pipe_args[114];
      pipe_args[0]=strtok(re_args[0],"|");
      while(1)
      {
        if(pipe_args[pipe_num]==NULL) {break;}
        pipe_args[++pipe_num] = strtok(NULL,"|");
      }
      char *t_pipe_args[114];
      if(pipe_num>=1)
      {
        for(int i=0;i<pipe_num-1;i++)
        {
          t_pipe_args[i] = malloc(sizeof(char)*strlen(pipe_args[i]));
          memset(t_pipe_args[i],0,strlen(pipe_args[i]));
          strcpy(t_pipe_args[i],pipe_args[i]);
        }
        if(file_args[1]!=NULL)
        {
          t_pipe_args[pipe_num-1] = malloc(sizeof(char)*(strlen(pipe_args[pipe_num-1])+1+strlen(file_args[1])));
          memset(t_pipe_args[pipe_num-1],0,strlen(pipe_args[pipe_num-1])+1+strlen(file_args[1]));
          strcpy(t_pipe_args[pipe_num-1],pipe_args[pipe_num-1]);
          strcat(t_pipe_args[pipe_num-1]," ");
          strcat(t_pipe_args[pipe_num-1],file_args[1]);
        }
        else
        {
          t_pipe_args[pipe_num-1] = malloc(sizeof(char)*strlen(pipe_args[pipe_num-1]));
          memset(t_pipe_args[pipe_num-1],0,strlen(pipe_args[pipe_num-1]));
          strcpy(t_pipe_args[pipe_num-1],pipe_args[pipe_num-1]);
        }
      }
      else
      {
        if(file_args[1]!=NULL)
        {
          t_pipe_args[0] = malloc(sizeof(char)*strlen(file_args[1]));
          memset(t_pipe_args[0],0,strlen(file_args[1]));
          strcpy(t_pipe_args[0],file_args[1]);
        }
        else
        {
          t_pipe_args[0] = NULL;
        }
      }
      
 
      if(pipe_num!=0) t_pipe_args[pipe_num]=NULL;
      else pipe_num++;
      if(t_pipe_count!=pipe_num-1) {printf("%s",error_message);fflush(stdout);return;}
      int rc=fork();
      if(rc<0)
      {
        printf("An error has occurred\n");
        return;
      }
      else if(rc==0)
      {
        handle_pipe(t_pipe_args,pipe_num,0,filepath,0);
        handle_pipe(after_pipe_args,after_pipe_num,0,NULL,1);
        exit(0);
      }
      else
      {
        int status;
        handle_pipe(t_pipe_args,pipe_num,1,filepath,0);
        //assert(0);
        handle_pipe(after_pipe_args,after_pipe_num,1,NULL,1);
        //assert(0);
        waitpid(rc,&status,0);
      }
      for(int i=0;i<pipe_num;i++) free(t_pipe_args[i]);
    }
    else
    {
      int pipe_num = 0;
      int t_pipe_count=0;
      for(int i=0;i<strlen(cmd_args);i++)
      { 
        if(cmd_args[i]=='|') t_pipe_count++;
      }
      char* pipe_args[114];
      pipe_args[0]=strtok(cmd_args,"|");
      if(pipe_args[0]==NULL) {printf("%s",error_message);fflush(stdout);return;}
      while(1)
      {
        if(pipe_args[pipe_num]==NULL) {break;}
        pipe_args[++pipe_num] = strtok(NULL,"|");
      }
      if(pipe_num!=t_pipe_count+1) {printf("%s",error_message);fflush(stdout); return;}
      int rc=fork();
      if(rc<0)
      {
        printf(" An error has occurred\n");
        return;
      }
      else if(rc==0)
      {
        handle_pipe(pipe_args,pipe_num,0,filepath,0);
        exit(0);
      }
      else
      {
        int status;
        handle_pipe(pipe_args,pipe_num,1,filepath,0);
        waitpid(rc,&status,0);
      }
    }
    fflush(stdout);
}


void handle_backg(char* back_args[],int back_num,bool is_main)
{
  for(int i=0;i<back_num;i++)
  {
    if(i==back_num-1&&is_main) { execute_once(back_args[i]);break;}
    trim(back_args[i]);
    int rc=fork();
    if(rc==0)
    {
      if(setpgid(0,0)<0)
      {
        printf(" An error has occurred\n");
        exit(0);
      }
      execute_once(back_args[i]);
      exit(0);
    }
    else
    {
      add_bg_task(rc,back_args[i]);
    }
  }
}

void handle_sigchld(int signum)
{
  while(waitpid(-1,NULL,WNOHANG)>0)
  {
    for(int i=0;i<bg_task_count;i++) 
    {  
      if(kill(bg_tasks[i].pid,0)==-1) 
      {  
        remove_bg_task(bg_tasks[i].pid);  
        break;  
      }  
    }
  }
}

void handle_multiple_cmd(char* cmd_args[],int cmd_num,bool if_have) 
{
  for(int i=0;i<cmd_num;i++)
  {
    int back_num = 0;
    int t_count = 0;
    bool if_double = 0;
    for(int j=0;j<strlen(cmd_args[i]);j++) 
    {
      if(cmd_args[i][j]=='&') 
      {
        t_count++; 
      }
      if(j!=strlen(cmd_args[i])-1) if(judge_near_neighbor(cmd_args[i],j,strlen(cmd_args[i])-1)) {printf("%s",error_message);fflush(stdout);if_double=1;break;}
    }
    if(if_double) continue;
    trim(cmd_args[i]);
    char* back_args[114];
    back_args[0] = strtok(cmd_args[i],"&");
    if(back_args[0]==NULL) {printf("%s",error_message);fflush(stdout);continue;}
    bool judge;
    while(1)
    {
      if(back_args[back_num]==NULL) break;
      judge=judge_spaces(back_args[back_num]);
      if(judge) break;
      back_args[++back_num] = strtok(NULL,"&");
    }
    if((i!=cmd_num-1&&judge)||(if_have&&judge)) {printf("%s",error_message);fflush(stdout);continue;}
    if(i!=cmd_num-1)
    {
      if(back_num!=t_count+1) {printf("%s",error_message);fflush(stdout);continue;}
      handle_backg(back_args,back_num,1);
    }
    else
    {
      if(if_have&&back_num!=t_count+1) {printf("%s",error_message);fflush(stdout);continue;}
      else if(!if_have)
      {
        if(back_num==t_count) handle_backg(back_args,back_num,0);
        else if(back_num==t_count+1) handle_backg(back_args,back_num,1);
        else {printf("%s",error_message);fflush(stdout);continue;}
      }
      else handle_backg(back_args,back_num,1);
    }
  
    
  }
  fflush(stdout);
}

int main()
{
  fflush(stdout);
  signal(SIGCHLD, handle_sigchld);
  strcpy(PATH,"/bin:");
  path_count=1;
  char* cmd = NULL;
  size_t len;
  printf("nsh> ");
  fflush(stdout);
  while(getline(&cmd,&len,stdin)>0)
  {

     bool js = 0;
     js = judge_spaces(cmd);
     if(js) {printf("nsh> ");fflush(stdout);continue;}
     char* buf = (char*)malloc(strlen(cmd)*sizeof(char));
     strcpy(buf,cmd);
     buf[strlen(cmd)-1] = '\0';
     trim(buf);
     int cmd_num = 0;

     int t_cmd_num = 0;
     bool if_double=0;
     bool if_first = 0;
     for(int i=0;i<strlen(buf);i++) 
     {
       if(buf[i]==';') 
       {
         t_cmd_num++;
         if(i!=strlen(buf)-1) 
         { 
           if(judge_neighbor(buf,i)) {printf("%s",error_message);fflush(stdout);if_double=1;break;}
         }
       }
     }
     if(if_double) {printf("nsh> ");
     fflush(stdout);
     continue;}
     
     if(buf[0]==';') if_first = 1;
     char *cmd_args[114];
     cmd_args[0]=strtok(buf,";");
     bool judge=0;
     while(1)
     {
       if(cmd_args[cmd_num]==NULL) break;
       judge = judge_spaces(cmd_args[cmd_num]);
       if(judge) break;
       cmd_args[++cmd_num] = strtok(NULL,";");
     }
     if(judge) {printf("%s",error_message);
     fflush(stdout);
     }
     else
     {
     if(t_cmd_num==cmd_num) handle_multiple_cmd(cmd_args,cmd_num,1);
     else if(t_cmd_num==cmd_num-1) handle_multiple_cmd(cmd_args,cmd_num,0);
     else
     {
       printf("%s",error_message);
       fflush(stdout);
     }
     }

     printf("nsh> ");
     fflush(stdout);
     free(buf);
  }
  return 0;
}


