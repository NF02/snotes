/* See LICENSE for license details */
/*
   ▄▀▀    ▀    ▀▀█                  █
 ▄▄█▄▄  ▄▄▄      █     ▄▄▄          █ ▄▄
   █      █      █    █▀  █         █▀  █
   █      █      █    █▀▀▀▀         █   █
   █    ▄▄█▄▄    ▀▄▄  ▀█▄▄▀    █    █   █

-------------------------------------------
Author: Nicola Ferru aka NFVblog
*/

static void help();
static void list_formats();
static void create_file(char name[], char format[], int date_form, char title[]);
static void remove_file(char cat[], char name[]);
static bool verformat(char *str);
static void list_directory(char *str);
static void engage(char *format,char *title, char *date, FILE *f);
static void openEditor(char *file);
static void verDir();
static bool checkFile(const char *filename);
static void openFile(const char *filename, const char *cat);
static char *getDate(int date_form);

// Functions developed
static void help ()
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
static void list_formats()
{
  printf("Format list:\n- html \n- Org Mode\n- Markdown\n");
}

static void create_file(char name[], char format[], int date_form, char title[])
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
    printf("Error: the note already exists");
    exit(-5);
  }
  note = fopen(file, "w"); 
  engage(format,title,dateNote,note);

  fclose(note);

  printf("The note was created in the format %s with the name %s in %s\n", format,name,file);

  // open text editor
  openEditor(file);
}

static bool verformat(char str[])
{
  // Function that checks for supported formats
  if(!strcmp(str, "org") || !strcmp(str, "md") || !strcmp(str, "html"))
    return true;
  else return false;
}

static void remove_file(char cat[], char name[])
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
    printf("Error: unable to delete the note\n");
  }
}

static void search(char *str)
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
  } else printf("Error: the directory does not exist!\n");
}

static void engage(char *format, char *title, char *date, FILE *f)
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
static void openEditor(char *file)
{
  char cmd[MAX_DIM_NAME_FILE*2];
  strcat(cmd,editor);
  strcat(cmd," ");
  strcat(cmd,file);
  strcat(cmd," &");
  system(cmd);
}

static void verDir(char *src)
{
  struct stat st = {0};
  if (stat(src, &st) == -1)
    mkdir(src, 0700);
}

static bool checkFile(const char *filename)
{
    FILE *file;
    if (file = fopen(filename, "r"))
    {
        fclose(file);
        return true;
    }

    return false;
}

static void openFile(const char *filename, const char *cat)
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

static char *getDate(int date_form)
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
    printf("Error: Invalid time setting");
    exit(-3);
  }
  return dateNote;
}
