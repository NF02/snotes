static void help();
static void list_formats();
static int create_file(char name[], char format[]);
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

static int create_file(char name[], char format[])
{
  char file[MAX_DIM_NAME_FILE];
  printf("nome %s formato %s", name,format);
  FILE *note;
  strcat(file,def_direct);
  strcat(file,name);
  strcat(file,".");
  strcat(file,format);
  note = fopen(file, "w");
  
  fclose(note);
}

static bool verformat(char str[])
{
  // Function that checks for supported formats
  if(!strcmp(str, "org") || !strcmp(str, "md") || !strcmp(str, "html"))
    return true;
  else return false;
}
