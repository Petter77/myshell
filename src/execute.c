#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

#include "../include/command.h"

int shell_scripts(char** args, int* proc_status) {
  // exit
  if (strcmp(args[0], "exit") == 0) {
    exit(EXIT_SUCCESS);
  }
  // cd
  if (strcmp(args[0], "cd") == 0) {
    if (args[1] == NULL) {
      chdir(getenv("HOME"));
    } else if (args[2] != NULL) {
      printf("cd: too many arguments\n");
      *proc_status = 1;
      return 1;
    } else {
      if (chdir(args[1]) != 0) {
        perror("cd");
        *proc_status = 1;
        return 1;
      }
    }
    *proc_status = 0;
    return 1;
  }
  return 0;
}

void execute(command_t cmd, int* proc_status) {
  int should_return = shell_scripts(cmd.args, proc_status);
  if (should_return) {
    return;
  }

  pid_t pid = fork();
  if (pid == 0) {
    if(cmd.redirect_in) {
      int flags = O_RDONLY;
      int fd = open(cmd.redirect_in, flags, 0644);
      dup2(fd, STDIN_FILENO);
      close(fd);
    }

    if (cmd.redirect_out) {
      int flags = O_WRONLY | O_CREAT | (cmd.append ? O_APPEND : O_TRUNC);
      int fd = open(cmd.redirect_out, flags, 0644);
      dup2(fd, STDOUT_FILENO);
      close(fd);
    }

    execvp(cmd.args[0], cmd.args);
  } else {
    waitpid(pid, proc_status, 0);
  }
}
