#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]){
  int i;

  if(argc < 2){
    printf(1, "Usage: rm files...\n");
    exit();
  }

  for(i = 1; i < argc; i++){
    if(unlink(argv[i]) < 0){
      printf(1, "rm: %s failed to delete\n", argv[i]);
      break;
    }
  }

  exit();
}
