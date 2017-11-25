#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	if(argc==1){
		//hanya memanggil fungsi tee
		char buffer[1025];
		while(fgets(buffer,1024,stdin)!=NULL)
			fputs(buffer,stdout);
	}
	else{
		//memanggil fungsi yang lain juga
	}
	return 0;
}