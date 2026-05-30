#pragma once

#include <stdlib.h>

typedef struct {
  char** args;
  char* redirect_in;
  char* redirect_out;
  int append;
} command_t;

command_t parse_command(char** start, char** end);
void command_free(command_t* com);

