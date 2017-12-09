#include "types.h"
#include "user.h"
#include "fcntl.h"

/*
Checklist:
- cek kalau ada parameter
- cek kalau ada input yang salah
- membuat beberapa file sekaligus
*/

int main(int argc, char *argv[])
{
	if(argc==1){
		//command invalid, hanya memanggil nama command saja
		printf(1,"invalid command\n");
	}
	else{
		if(argc==2){
			int fd = open(argv[1],O_CREATE | O_RDWR);
			if(fd >= 0){
				printf(1,"Create file succeed!\n");
			}
			close(fd);
		}
		else{
			int i;
			for(i=1;i<argc;++i){
				int fd = open(argv[i],O_CREATE | O_RDWR);
				close(fd);
			}
		}
	}

	exit();
}
