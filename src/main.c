#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include "../include/input.h"
#include "../include/execute.h"
#include "../include/prompt.h"
#include "../include/command.h"

void shell_loop(void) {
  char *input;
  int should_run = 1;
  int proc_status = 0;

  do {
    print_indicator(proc_status);
    input = get_input();
    command_t* command = get_args(input);
    command = get_args(input);

    if (command->args[0] == NULL) continue;
    execute(command->args, &proc_status);

    free(input);
    command_free(command);
  } while (should_run);
}

int main() {
  shell_loop();

  return EXIT_SUCCESS;
}
