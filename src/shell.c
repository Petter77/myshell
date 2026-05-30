#include <stdlib.h>
#include "../include/pipeline.h"
#include "../include/input.h"
#include "../include/input.h"
#include "../include/prompt.h"

void shell_loop(void) {
  char *input;
  int should_run = 1;
  int proc_status = 0;

  do {
    print_indicator(proc_status);
    input = get_input();
    char** args = get_tokens(input);

    if (args[0] == NULL) {
      for (int i = 0; args[i] != NULL; i++) {
        free(args[i]);
      }
      free(input);
      continue;
    }
    pipeline_t pipeline = build_pipeline(args);
    execute_pipeline(&pipeline, &proc_status);
    free(input);
    free(args);
    pipeline_free(&pipeline);
  } while (should_run);
}
