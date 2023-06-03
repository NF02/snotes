/* See LICENSE for license details */
static void printerr(char *err, int err_code);


// print instruction for errors
static void printerr(char *err, int err_code)
{
  printf("Error %d: %s\n",err_code, err);
  exit(err_code);
}
