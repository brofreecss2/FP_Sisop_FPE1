#include "types.h"
#include "stat.h"
#include "user.h"

/*
Checklist
- Masih belum bisa handle SIGSTOP atau SIGKILL
- Tambah fungsi untuk cek parameter
*/



int main(int argc, char const *argv[])
{
	char buffer[1025];
	char print[1025];

	print = gets(buffer,1024);
	printf(1,"%s\n",print);

}