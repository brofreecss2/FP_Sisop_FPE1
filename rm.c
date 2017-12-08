#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

int main(int argc, char *argv[]){
  int i;

  if(argc < 2){
    printf(2, "Usage: rm files...\n");
    exit();
  }

  int rem_dir = 0;

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


    if(unlink(argv[i]) < 0){
      printf(2, "rm: %s failed to delete\n", argv[i]);
      break;
    }
  }

  exit();
}
