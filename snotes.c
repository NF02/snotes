#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// dedicated libs
#include "libs/consts.h"
#include "config.h"
#include "libs/file.h"


int main(int argc, char *argv[])
{
  if (argc == 2 && !strcmp("-h", argv[1]))
    help();
  else if (argc==2 && !strcmp("-F", argv[1]))
    list_formats();
  else if (argc==3 && !strcmp("new", argv[1]))
    create_file(argv[2],"org",defDateForm);
  else if (argc==5 && !strcmp("new", argv[1]) && verformat(argv[3]) &&
	   !strcmp("-f", argv[2]))
    create_file(argv[4],argv[3],defDateForm);
  else return 0;
}
