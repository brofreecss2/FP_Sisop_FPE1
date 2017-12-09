#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

/*
Checklist
- handle file dalam folder (rekursif?)
*/

int rem_dir;

void rm(char *path){
  char *buf = (char*)malloc(1024*sizeof(char));
  struct dirent de;
  struct stat st;

  int dir = open(path,0);
  if(dir < 0){
    printf(2,"rm: cannot access '%s': No such file or directory\n",path);
    return;
  }

  if(fstat(dir,&st) < 0){
    printf(2,"rm: cannot stat '%s'\n",path);
    close(dir);
    return;
  }

  if(st.type == T_FILE){
    close(dir);
    if(unlink(path) < 0){
      printf(2, "rm: %s failed to delete\n", path);
    }
    exit();
  }
  else if(st.type == T_DIR && rem_dir){
//    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
//      printf(1,"ls: path too long\n");
//      return;
//    }
    strcpy(buf,path);
    char *p = buf+strlen(buf);
    *p++ = '/';
    int cnt=0;

    while(read(dir,&de,sizeof (de)) == sizeof (de)){
      if(de.inum == 0)continue;
      memmove(p,de.name,DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf,&st) < 0){
        printf(2,"ls: cannot stat '%s'\n",buf);
        continue;
      }
      cnt++;
      if(cnt <= 2)continue;
      rm(buf);
      //printf(1,"%s %d %d %d\n",backname(buf),st.type,st.ino,st.size);
      if(unlink(buf) < 0){
        printf(2, "rm: %s failed to delete\n", buf);
      }
    }
  }
  close(dir);
  return;
}

int main(int argc, char *argv[]){
  int i;

  if(argc < 2){
    printf(2, "Usage: rm files...\n");
    exit();
  }

  rem_dir = 0;

  for(i = 1; i < argc; i++){
//  struct dirent de;
    struct stat st;

    if(argv[i][0] == '-'){
      if(argv[i][1] == 'r') rem_dir = 1;
      continue;
    }

    int path = open(argv[i],0);
    if(path < 0){
      printf(2,"rm: cannot access '%s' : No such file or directory\n",argv[i]);
      exit();
    }
    if(fstat(path,&st) < 0){
      printf(2,"rm: cannot stat '%s'\n",argv[i]);
      exit();
    }
    if(st.type == T_DIR){
      if(rem_dir == 0){
        printf(2,"rm: cannot delete '%s' : Is a directory\n",argv[i]);
        break;
      }
    }
    close(path);

    rm(argv[i]);
    unlink(argv[i]);
  }
  exit();
}
