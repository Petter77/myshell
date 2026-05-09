#include "../include/command.h"

void command_free(command_t* cmd) {
  for (int i = 0; cmd->args[i] != NULL; i++) {
    free(cmd->args[i]);
  }
  free(cmd->args);
}
