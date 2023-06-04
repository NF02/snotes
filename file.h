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
#ifndef FILE_H_
#define FILE_H_
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
static char *getDate(int date_form); // gen current date
static void printerr(char *err, int err_code);
#endif
