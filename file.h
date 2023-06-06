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
void search(char *str);
#endif
