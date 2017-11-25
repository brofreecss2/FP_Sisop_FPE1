#include <stdio.h>

/*
Checklist:
- cek kalau ada parameter
*/

int main(int argc, char const *argv[])
{
	if(argc==1){
		puts("touch: missing file operand");
		return 0;
	}

	FILE* out = fopen(argv[1],"w");
	fclose(out);

	return 0;
}