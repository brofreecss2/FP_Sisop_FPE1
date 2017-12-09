#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

char *backname(char *path){
	char *p;

	for(p = path + strlen(path);p>=path && *p != '/';p--);
	p++;

	return p;
}

char *strcat_hehe(char *dest,char *src){
	char *rdest = dest;
	while(*dest) dest++;
	while((*dest++ = *src++));
	return rdest;
}

int copyfiles(char *src,char *dst){
	int fd0,fd1,n;
	char buf[1024];
	if((fd0 = open(src,O_RDONLY)) < 0){
		printf(1,"cp: cannot open %s\n",src);
		exit();
	}
	if((fd1 = open(dst, O_CREATE | O_WRONLY)) < 0){
		printf(1,"cp: cannot open %s\n",dst);
		exit();
	}

	while((n = read(fd0,buf,sizeof(buf))) > 0){
		write(fd1,buf,n);
	}
	close(fd0);
	close(fd1);
	return 0;
}

int main(int argc, char *argv[])
{
	if(argc<=2){
		printf(1,"Need 2 arguments!\n");
		exit();
	}

	char awal[1024] ;
	strcpy(awal,argv[argc-2]);
	char akhir[1024];
	strcpy(akhir,argv[argc-1]);

	int m = strlen(awal);
	int n = strlen(akhir);
//	printf(1,"%s %s\n",backname(argv[argc-2]),argv[argc-1]);

	int o1,o2;
	//struct dirent d1,d2;
	struct stat st1,st2;
	if(awal[m-1]!='/' && akhir[n-1]!='/'){
		copyfiles(awal,akhir);
		unlink(awal);
		exit();
	} // bukan direktori

	if((o1 = open(argv[argc-2],0)) < 0){
		printf(2,"cp: cannot open '%s'\n",argv[argc-2]);
		exit();
	}
	if(fstat(o1,&st1) < 0){
		printf(2,"cp: cannot open '%s'\n",argv[argc-2]);
		close(o1);
		exit();
	}

	if((o2 = open(argv[argc-1],0)) < 0){
		printf(2,"cp: cannot open '%s'\n",argv[argc-1]);
		close(o1);
		exit();
	}
	if(fstat(o2,&st2) < 0){
		printf(2,"cp: cannot open '%s'\n",argv[argc-1]);
		close(o1);
		close(o2);
		exit();
	}

	if(st1.type == T_FILE && st2.type == T_DIR){ // file dan folder
		close(o1);
		close(o2);

		//char *new_dest = strcat_hehe(argv[argc-1],"/");
		char *new_dest = strcat_hehe(argv[argc-1],backname(argv[argc-2]));
		printf(1,"%s %s\n",awal,new_dest);
		copyfiles(awal,new_dest);
		unlink(awal);
		exit();
	}

	// else if(st1.type == T_DIR && st2.type == T_DIR){
	// 	struct dirent de;
	// 	close(o2);
	// 	char buf[1024];

	// 	if(strlen(awal) + 1 + DIRSIZ + 1 > sizeof buf){
	// 		printf(1,"cp: path too long\n");
	// 		exit();
	// 	}
	// 	strcpy(buf,awal);
	// 	char *p = buf+strlen(buf);
	// 	*p++ = '/';
	// 	int cnt = 0;
	// 	while(read(o1,&de,sizeof (de)) == sizeof (de)){
	// 		if(de.inum == 0)continue;
	// 		memmove(p,de.name,DIRSIZ);
	// 		p[DIRSIZ] = 0;
	// 		if(stat(buf,&st1) < 0){
	// 			printf(2,"cp: cannot stat '%s'\n",buf);
	// 			continue;
	// 		}

	// 		cnt++;
	// 		if(cnt <= 2)continue;

	// 		char *new_dest = strcat_hehe(argv[argc-1],backname(buf));
	// 		//printf(1,"%s %s\n",buf,new_dest);
	// 		copyfiles(buf,new_dest);
	// 	}
	// 	close(o1);
	// 	exit();
	// }
	exit();
}