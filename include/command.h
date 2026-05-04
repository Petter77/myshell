#ifndef MYSHELL_INCLUDE_COMMAND_H_
#define MYSHELL_INCLUDE_COMMAND_H_

#include <stdlib.h>

typedef struct {
  char** args;
  char* redirect_in;
  char* redirect_out;
  int append;
} command_t;

void command_free(command_t* com);

#endif  // MYSHELL_INCLUDE_COMMAND_H_
