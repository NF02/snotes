#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h> 

// dedicated libs
#include "libs/consts.h"
#include "config.h"
#include "libs/file.h"


int main(int argc, char *argv[])
{
  verDir(def_direct);
  if (argc == 2 && !strcmp("-h", argv[1]))
    help();
  else if (argc == 2 && !strcmp("-v", argv[1]))
    printf("SNotes-%s",VERSION);
  else if (argc==2 && !strcmp("-F", argv[1]))
    list_formats();
  else if (argc==3 && !strcmp("new", argv[1]))
    create_file(argv[2],def_format,defDateForm,argv[2]);
  else if (argc==3 && !strcmp("-l", argv[1]))
    search(argv[2]);
  else if (argc==5 && !strcmp("new", argv[1]) && verformat(argv[3]) &&
	   !strcmp("-f", argv[2]))
    create_file(argv[4],argv[3],defDateForm,argv[4]);
  else if (argc==5 && !strcmp("new", argv[1]) && !strcmp("-t", argv[3]))
    create_file(argv[2],def_format,defDateForm,argv[4]);
  else if (argc==5 && !strcmp("-R", argv[1]) && !strcmp("-c", argv[3]))
    remove_file(argv[4],argv[2]);
  else help();
    return 0;
}
