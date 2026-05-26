#include <string.h>
#include <stdio.h>
#include "../include/pipeline.h"
#include "../include/input.h"
#include "../include/execute.h"

pipeline_t build_pipeline(char** tokens) {
  pipeline_t pipeline;
  pipeline.count = 1;
  for (size_t i = 0; tokens[i] != NULL; i++) {
    if (strcmp(tokens[i], "|") == 0) {
      pipeline.count++;
    }
  }
  pipeline.commands = malloc(sizeof(command_t) * (pipeline.count));
  char** start = tokens;
  char** end = tokens;
  size_t command_index = 0;
  for (size_t i = 0;; i++) {
    if (*end == NULL) {
      pipeline.commands[command_index] = parse_command(start, end-1);
      command_index++;
      break;
    } else if (strcmp(*end, "|") == 0) {
      pipeline.commands[command_index] = parse_command(start, end-1);
      command_index++;
      end++;
      start = end;
    } else {
      end++;
    }
  }
  printf("count: %zu\n", pipeline.count);
  for (size_t i = 0; i < pipeline.count; i++) {
    printf("cmd %zu: %s\n", i, pipeline.commands[i].args[0]);
  }
  return pipeline;
}

void execute_pipeline(pipeline_t *pipeline, int* exit_code) {
  if (pipeline->count == 1) {
    execute(pipeline->commands[0], exit_code);
  }
}

void print_pipeline(pipeline_t *pipeline) {
  for (size_t i = 0; i < pipeline->count; i++) {
    for (size_t j = 0; pipeline->commands[i].args[j] != NULL; j++) {
      printf("%s ", pipeline->commands[i].args[j]);
    }
    printf("\n");
  }
}
