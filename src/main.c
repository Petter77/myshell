#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

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
    char** args = get_args(input);

    if (args[0] == NULL) continue;
    command_t cmd = parse_command(args);
    execute(cmd, &proc_status);

    free(input);
    free_args(args);
  } while (should_run);
}

int main() {
  shell_loop();

  return EXIT_SUCCESS;
}
