#ifndef LAUNCH_H
#define LAUNCH_H

#include "main.h"
#include "fgbg.h"
#include "builtins.h"


void check_zombie();
int launch_job( struct job* job);
int launch_process(struct job* job, struct process *proc , int in_fd, int out_fd, int mode);
int execute_builtin_command( struct process *proc, struct job* job);

#endif