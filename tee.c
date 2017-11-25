#include <stdio.h>
#include <string.h>

/*
Checklist
- Masih belum bisa handle SIGSTOP atau SIGKILL
- Tambah fungsi untuk cek parameter
*/

int main(int argc, char const *argv[])
{
	char buffer[1025];
	printf("%s %s\n",argv[0],argv[1]);
	if(argc==1){
		//hanya memanggil fungsi tee
		while(fgets(buffer,1024,stdin)!=NULL)
			fputs(buffer,stdout);
	}
	else{
		//memanggil implementasi yang lain juga
		if(argc==2){
			// hanya nama fungsi dan nama file
			FILE *out = fopen(argv[1],"w");
			while(fgets(buffer,1024,stdin)!=NULL){
				fputs(buffer,stdout);
				fputs(buffer,out);
			}
			fclose(out);
		}

		//ada parameter yang lain
	}
	return 0;
}