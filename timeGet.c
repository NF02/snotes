#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "file.h"
#include "config.h"

char *getDate(int date_form); // get current date
char *getHours_note(); // get current hours (HH:MM)
char *getHours(); // get current Hours
char *getMins(); // get current minutes

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

char *getHours_note()
{
  char *hourNote=malloc(sizeof(char) * 3);
  time_t t;
  
  t=time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(hourNote, "%d:%d", tm.tm_hour,tm.tm_min);
  return hourNote;
}

char *getHours()
{
  time_t t;
  char *hourNote=malloc(sizeof(char));
  t=time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(hourNote, "%d", tm.tm_hour);
  return hourNote;
}

char *getMins()
{
  time_t t;
  char *minNote=malloc(sizeof(char));
  t=time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(minNote, "%d", tm.tm_min);
  return minNote;
}

