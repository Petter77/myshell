#include "../include/command.h"


void command_free(command_t* cmd) {
    if (cmd->redirect_out) free(cmd->redirect_out);
    if (cmd->redirect_in)  free(cmd->redirect_in);
    for (int i = 0; cmd->args[i] != NULL; i++) {
        free(cmd->args[i]);
    }
    free(cmd->args);
}
