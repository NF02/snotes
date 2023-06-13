/* See LICENSE for license details */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h> 
#include <git2.h>
// dedicated libs
#include "consts.h"
#include "config.h"
#include "file.h"
#include "timeGet.h"
//#include "libs/gitSync.h"

int main(int argc, char *argv[])
{ 
  verDir(def_direct);
  if(argc == 2){
    if (!strcmp("-h", argv[1]) || !strcmp("--help", argv[1]))
	help();
    else // print version
     if (!strcmp("-v", argv[1]) || !strcmp("--version", argv[1]))
        printf("SNotes-%s\n",VERSION);
    else // print the list of formats
     if (!strcmp("-F", argv[1]) || !strcmp("--formats-list", argv[1]))
	list_formats();
  }else if (argc==3) {// create a file with default extension
    if (!strcmp("new", argv[1]))
	create_file(argv[2],def_format,defDateForm,argv[2]);
    else // list of directory 
     if (!strcmp("-l", argv[1]) || !strcmp("--list-directory", argv[1]))
	search(argv[2]);
    else // open a file
     if (!strcmp("open", argv[1])) 
	openFile(argv[2],getDate(defDateForm));
    else
     if (!strcmp("-R", argv[1]) || !strcmp("--remove", argv[1]))
        remove_file(argv[2],getDate(defDateForm));
  }else if (argc == 5) {// creates a file with the format chosen by the user
     if (!strcmp("new", argv[1]) && verformat(argv[3]) && !strcmp("-f", argv[2]))
	create_file(argv[4],argv[3],defDateForm,argv[4]);
     else // creates a file with a title chosen by the author
      if (!strcmp("new", argv[1]) && !strcmp("-t", argv[3]))
	create_file(argv[2],def_format,defDateForm,argv[4]);
     else // removes a file by name and by day created.
      if ((!strcmp("-R", argv[1]) || !strcmp("--remove", argv[1])) && (!strcmp("-c", argv[3]) || !strcmp("--category", argv[3])))
	remove_file(argv[4],argv[2]);
     else // removes a file by name and by day created. 
      if (!strcmp("open", argv[1]) && (!strcmp("-c", argv[3]) || !strcmp("--category", argv[3])))
	openFile(argv[2],argv[4]);
  }else help();
  return 0;
}
