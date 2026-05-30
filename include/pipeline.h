#pragma once

#include "command.h"

typedef struct {
  command_t* commands;
  size_t count;
} pipeline_t;

pipeline_t build_pipeline(char** tokens);
void execute_pipeline(pipeline_t *pipeline, int* exit_code);
void print_pipeline(pipeline_t *pipeline);
void pipeline_free(pipeline_t *pipeline);

