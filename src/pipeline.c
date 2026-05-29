#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
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
      free(*end);
      command_index++;
      end++;
      start = end;
    } else {
      end++;
    }
  }
  return pipeline;
}

void execute_pipeline(pipeline_t *pipeline, int* exit_code) {
  if (pipeline->count == 1) {
    execute(pipeline->commands[0], exit_code);
  } else {
    int proc_status;
    int fd[2];
    pid_t pid[2];
    pipe(fd);
    pid[0] = fork();
    if (pid[0] == 0) { // ls 
      dup2(fd[1], STDOUT_FILENO);
      close(fd[0]);
      close(fd[1]);
      execvp(pipeline->commands[0].args[0], pipeline->commands[0].args);
    } 

    pid[1] = fork();
    if (pid[1] == 0) { // grep 
      dup2(fd[0], STDIN_FILENO);
      close(fd[0]);
      close(fd[1]);
      execvp(pipeline->commands[1].args[0], pipeline->commands[1].args);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid[0], &proc_status, 0);
    waitpid(pid[1], &proc_status, 0);
  }
}

void pipeline_free(pipeline_t *pipeline) {
  for (size_t i = 0; i < pipeline->count; i++) {
    command_free(&pipeline->commands[i]);
  }
  free(pipeline->commands);
}

void print_pipeline(pipeline_t *pipeline) {
  for (size_t i = 0; i < pipeline->count; i++) {
    for (size_t j = 0; pipeline->commands[i].args[j] != NULL; j++) {
      printf("%s ", pipeline->commands[i].args[j]);
    }
    printf("\n");
  }
}
