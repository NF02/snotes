#include <stdio.h>
#include <stdlib.h>
#include <git2.h>
#include <stdbool.h>
#include <string.h>
#include "config.h"

void gitInit();


void gitInit(){
  char *dir = malloc(sizeof(char) * strlen(def_direct));
  strcat(dir,def_direct);
  git_repository *repo = NULL;
  git_repository_init(&repo, dir, false);
  
}
