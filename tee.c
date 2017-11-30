#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

/*
Checklist
- Tambah fungsi untuk cek parameter
*/

char buffer[1025];

int main(int argc, char *argv[])
{
	int fd,n;
	if(argc==2){
		if((fd = open(argv[1], O_CREATE | O_RDWR)) < 0){
			printf(1,"tee: cannot open %s\n",argv[1]);
			exit();
		}
	}

	while(1){
		n = read(0,buffer,sizeof buffer);
		if(n==0)break;
		if(strcmp(buffer,"")==0)break;

		if(n < 0){
			printf(1,"tee: read error\n");
			exit();
		}

		if(write(1,buffer,n) != n){
			printf(1,"write error\n");
		}
		if(argc==2){
			if(write(fd,buffer,n) != n){
				printf(1,"tee: write error\n");
			}
		}
	}
	
	if(argc==2)close(fd);
	printf(1,"\n");
	exit();
}