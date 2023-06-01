static void help();
static void list_formats();
static int create_file(char name[], char format[], int date_form);
static bool verformat(char *str);

// Functions developed
static void help ()
{
  printf("SNotes [Simple Notes]\n --help [-h]: Print help with all commands\n --formats-list [-F]: View the list of formats\n");
}

static void list_formats()
{
  printf("Format list:\n html \n Org Mode\n Markdown\n");
}

static int create_file(char name[], char format[], int date_form)
{
  char file[MAX_DIM_NAME_FILE];
  

  time_t t;
  
  t=time(NULL);
  struct tm tm = *localtime(&t);
  
  FILE *note;
  strcat(file,def_direct);
  char string[DATE_DIM];
  switch (date_form) {
  case 1:
    sprintf(string, "%d-%d-%d/", tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
    break;
  case 2:
    sprintf(string, "%d-%d-%d/", tm.tm_mon+1,tm.tm_mday,tm.tm_year+1900);
    break;
  case 3:
    sprintf(string, "%d-%d-%d/", tm.tm_year+1900, tm.tm_mon+1,tm.tm_mday);
    break;
  }
  strcat(file,string);

  struct stat st = {0};
  if (stat(file, &st) == -1)
    mkdir(file, 0700);
  strcat(file,name); 
  strcat(file,".");
  strcat(file,format);
  note = fopen(file, "w");
  fclose(note);
  printf("The note was created in the format %s with the name %s in %s", format,name,file);
}

static bool verformat(char str[])
{
  // Function that checks for supported formats
  if(!strcmp(str, "org") || !strcmp(str, "md") || !strcmp(str, "html"))
    return true;
  else return false;
}

