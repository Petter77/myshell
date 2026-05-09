#ifndef MYSHELL_INCLUDE_EXECUTE_H_
#define MYSHELL_INCLUDE_EXECUTE_H_

#include "command.h"

int shell_scripts(char** args, int* proc_status);
void execute(command_t cmd, int* proc_status);

#endif  // MYSHELL_INCLUDE_EXECUTE_H_
