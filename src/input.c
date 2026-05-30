#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/input.h"

#define BUFFER_SIZE 1024

char* get_input() {
  char* input = malloc(sizeof(char) * BUFFER_SIZE);
  fgets(input, BUFFER_SIZE, stdin);
  input[strcspn(input, "\n")] = '\0';

  return input;
}

char **get_tokens(char *input) {
  int cap = 2;
  int count = 0;
  char **args = malloc(sizeof(char *) * cap);

  char *start = input;
  while (*start != '\0') {
    while (*start == ' ') start++;
    if (*start == '\0') break;

    char *end = start;
    while (*end != ' ' && *end != '\0') end++;

    int len = end - start;
    char *token = malloc(len + 1);
    strncpy(token, start, len);
    token[len] = '\0';

    if (count + 1 >= cap) {
      cap *= 2;
      args = realloc(args, sizeof(char *) * cap);
    }
    args[count++] = token;
    
    start = end;
  }

  args[count] = NULL;
  return args;
}



