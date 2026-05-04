#include "../include/command.h"

void command_free(command_t* com) {
   free(com->args);
}
