#ifndef MYSHELL_INCLUDE_INPUT_H_
#define MYSHELL_INCLUDE_INPUT_H_

#include "command.h"

char* get_input();
char** get_tokens(char *input);
command_t parse_command(char** start, char** end);

#endif  // MYSHELL_INCLUDE_INPUT_H_
