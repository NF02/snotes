/* See LICENSE for license details */
/*
  
   ▒██    █    ███
   █░            █
   █             █
 █████  ███      █     ███           ▓██▒
   █      █      █    ▓▓ ▒█         ▓█  ▓
   █      █      █    █   █         █░
   █      █      █    █████         █
   █      █      █    █             █░
   █      █      █░   ▓▓  █    █    ▓█  ▓
   █    █████    ▒██   ███▒    █     ▓██▒

-------------------------------------------
Author: Nicola Ferru aka NFVblog
*/


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
#include"consts.h"
#include"config.h"


void help();
void list_formats();
void create_file(char name[], char format[], int date_form, char title[]);
void remove_file(char cat[], char name[]);
bool verformat(char *str);
void list_directory(char *str);
void engage(char *format,char *title, char *date, FILE *f);
void openEditor(char *file);
void verDir();
bool checkFile(const char *filename);
void openFile(const char *filename, const char *cat);
char *getDate(int date_form); // gen current date
void printerr(char *err, int err_code);
// Functions developed
void help ()
{
  printf("┏━┛┏━ ┏━┃━┏┛┏━┛┏━┛\n");
  printf("━━┃┃ ┃┃ ┃ ┃ ┏━┛━━┃\n");
  printf("━━┛┛ ┛━━┛ ┛ ━━┛━━┛\n\
------------------------------------------------------------------------------\n");
  printf(" \
  --help                [-h]: Print help with all commands\n \
  --formats-list        [-F]: View the list of formats\n \
  --remove              [-R]: remove notes or directories\n \
  --category            [-c]: search by category\n \
  --list-directory      [-l]: list of directory\n \
  --tree-of-directory   [-T]: Print all the contents of the Notes directory\n");
  
}

// file manager
void list_formats()
{
  printf("Format list:\n- html \n- Org Mode\n- Markdown\n");
}

void create_file(char name[], char format[], int date_form, char title[])
{
  char file[MAX_DIM_NAME_FILE];
  

  FILE *note;
  strcat(file,def_direct);
  char *dateNote = getDate(date_form);
  
  strcat(file,dateNote);
  strcat(file,"/");
  
  verDir(file);
  strcat(file,name);
  strcat(file,".");
  strcat(file,format);
  if (checkFile(file)){
    printerr("The file already exists",-2);
  } else {
    note = fopen(file, "w"); 
    engage(format,title,dateNote,note);

    fclose(note);

    printf("The note was created in the format %s with the name %s in %s\n", format,name,file);

    // open text editor
    openEditor(file);
  }
}

bool verformat(char str[])
{
  // Function that checks for supported formats
  if(!strcmp(str, "org") || !strcmp(str, "md") || !strcmp(str, "html"))
    return true;
  else return false;
}

void remove_file(char cat[], char name[])
{
  char file[MAX_DIM_NAME_FILE];
  int removed;
  FILE *note;
  strcat(file,def_direct);
  strcat(file,cat);
  strcat(file,"/");
  strcat(file,name);
  removed = remove(file);
  if(removed == 0) {
    printf("Note deleted successfully\n");
  } else {
    printerr("Note does not exist",-6);
  }
}

void search(char *str)
{
  char directory[MAX_DIM_NAME_FILE];
  strcat(directory,def_direct);
  strcat(directory,str);
  DIR *d;
  struct dirent *dir;
  d = opendir(directory);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      printf("%s\n", dir->d_name);
    } 
    closedir(d);
  } else printerr("the directory does not exist",-4);
}

void engage(char *format, char *title, char *date, FILE *f)
{ 
  if (!strcmp("org", format))
    fprintf (f, "#+author: %s\n#+title: %s\n#+date: %s \n\n* %s\n",author, title,\
	     date,title);
  else if (!strcmp("md", format))
     fprintf (f, "---\nauthor: %s\ntitle: %s\ndate: %s\n--- \n\n# %s\n",author, title,\
	     date,title);
  else if (!strcmp("html", format))
    fprintf (f, "<!-- author: %s title: %s date: %s -->\n <!DOCTYPE html>\n \
	<html lang="">\n<head>\n<title>%s</title>\n<meta charset=\"utf-8\">\n</head>\n<body>\n \
<h1>%s<h1>\n\n</body>\n</html>",author, title, date,title,def_lang,title);
  else if (!strcmp("txt", format))
    fprintf (f, "author: %s\ntitle: %s\ndate: %s \n------------\n",author, title, \
	     date);

}
void openEditor(char *file)
{
  char cmd[MAX_DIM_NAME_FILE*2];
  strcat(cmd,editor);
  strcat(cmd," ");
  strcat(cmd,file);
  strcat(cmd," &");
  system(cmd);
}

void verDir(char *src)
{
  struct stat st = {0};
  if (stat(src, &st) == -1)
    mkdir(src, 0700);
}

bool checkFile(const char *filename)
{
    FILE *file;
    if (file = fopen(filename, "r"))
    {
        fclose(file);
        return true;
    }

    return false;
}

void openFile(const char *filename, const char *cat)
{
  char file[MAX_DIM_NAME_FILE];
  strcat(file,def_direct);
  strcat(file,cat);
  strcat(file,"/");
  strcat(file,filename);
  //printf("%s",file); // debug instruction
  if(checkFile(file))
    {
      openEditor(file);
    }
}

char *getDate(int date_form)
{
  char *dateNote=malloc(sizeof(char) * 6);
  time_t t;
  
  t=time(NULL);
  struct tm tm = *localtime(&t);
  switch (date_form) {
  case 1:
    sprintf(dateNote, "%d-%d-%d", tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
    break;
  case 2:
    sprintf(dateNote, "%d-%d-%d", tm.tm_mon+1,tm.tm_mday,tm.tm_year+1900);
    break;
  case 3:
    sprintf(dateNote, "%d-%d-%d", tm.tm_year+1900, tm.tm_mon+1,tm.tm_mday);
    break;
  default:
    printerr("the date format is invalid",-1);
  }
  return dateNote;
}

// print instruction for errors
void printerr(char *err, int err_code)
{
  printf("Error %d: %s\n",err_code, err);
  exit(err_code);
}
