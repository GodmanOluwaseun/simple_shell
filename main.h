#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int ac, char **av, char **env);
char **split_string(char *str);
int exec_child(char *argv, char **av, char **env);

#endif /* MAIN_H */
