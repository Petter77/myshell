#include "../include/command.h"
#include <stdlib.h>
#include <string.h>

void command_free(command_t* cmd) {
    if (cmd->redirect_out) free(cmd->redirect_out);
    if (cmd->redirect_in)  free(cmd->redirect_in);
    for (int i = 0; cmd->args[i] != NULL; i++) {
        free(cmd->args[i]);
    }
    free(cmd->args);
}

command_t parse_command(char** start, char** end) {
  size_t len = end - start + 1;
  char** args = malloc(sizeof(char*) * (len + 1));
  memcpy(args, start, len * sizeof(char*));
  args[len] = NULL;
  command_t cmd;
  cmd.args = args;
  cmd.redirect_in = NULL;
  cmd.redirect_out = NULL;
  cmd.append = 0;

  for (int i = 0; args[i] != NULL; i++) {
    if (strcmp(args[i], ">") == 0 && args[i+1] != NULL) {
      cmd.redirect_out = args[i+1];
      cmd.append = 0;
      free(args[i]);
      args[i] = NULL;
      args[i+1] = NULL;       
      i++;
    } else if (strcmp(args[i], ">>") == 0 && args[i+1] != NULL) {
      cmd.redirect_out = args[i+1];
      cmd.append = 1;
      free(args[i]);
      args[i] = NULL;
      args[i+1] = NULL;       
      i++;
    } else if (strcmp(args[i], "<") == 0 && args[i+1] != NULL) {
      cmd.redirect_in = args[i+1];
      free(args[i]);
      args[i] = NULL;
      args[i+1] = NULL;       
      i++;
    }
  }

  return cmd;
}
