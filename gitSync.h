#ifndef GITSYNC_H_
#define GITSYNC_H_
void gitInit();
void gitClone();
void gitCommit(char *message, char *file);
void gitAdd(char *file);

#endif
