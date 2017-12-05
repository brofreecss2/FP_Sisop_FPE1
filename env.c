#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
  char *env[] = environ;
  int i = 0;

  for(; env[i] != 0; i++){
    printf(1, "%s\n", env[i]);
  }
  exit();
}