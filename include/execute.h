#pragma once

#include "command.h"

int shell_scripts(char** args, int* proc_status);
void execute(command_t cmd, int* proc_status);

