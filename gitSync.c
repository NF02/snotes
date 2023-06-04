#include "gitSync.h"

static void gitInit();


static void gitInit(){
  char *dir = malloc(sizeof(char) * strlen(def_direct));
  strcat(dir,def_direct);
  git_repository *repo = NULL;
  git_repository_init(&repo, dir, false);
  
}
