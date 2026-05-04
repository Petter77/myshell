#ifndef MYSHELL_INCLUDE_INPUT_H_
#define MYSHELL_INCLUDE_INPUT_H_

#include "command.h"

char* get_input();
command_t* get_args(char *input);

#endif  // MYSHELL_INCLUDE_INPUT_H_
