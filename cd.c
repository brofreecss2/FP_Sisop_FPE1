#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

/*
Checklist:
- error handling kalau file
- tulisan error handling
*/

int main(int argc, char *argv[])
{
	if(argc < 2){
		//argument missing
		exit();
	}

	chdir(argv[1]);
	exit();
}