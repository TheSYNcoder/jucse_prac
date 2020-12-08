#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <pwd.h>
#include <time.h>
#include <glob.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define NR_JOBS 20
#define PATH_BUFSIZE 1024
#define COMMAND_BUFSIZE 1024
#define TOKEN_BUFSIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"
#define MAX_HISTORY 1024

#define BACKGROUND_EXECUTION 0
#define FOREGROUND_EXECUTION 1
#define PIPELINE_EXECUTION 2

#define COLOR_NONE "\033[m"
#define COLOR_RED "\033[1;37;41m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_CYAN "\033[0;36m"
#define COLOR_GREEN "\033[0;32;32m"
#define COLOR_GRAY "\033[1;30m"

#define STATUS_RUNNING 0
#define STATUS_DONE 1
#define STATUS_SUSPENDED 2
#define STATUS_CONTINUED 3
#define STATUS_TERMINATED 4

#define COMMAND_EXTERNAL 0
#define COMMAND_FG 1
#define COMMAND_BG 2
#define COMMAND_MKDIR 3
#define COMMAND_INFO 4
#define COMMAND_EXIT 5
#define COMMAND_EDIT 6
#define COMMAND_MAN 7


const char *STATUS_STRING[] = {
    "running",
    "done",
    "suspended",
    "continued",
    "terminated"
};

struct process
{
    char *command;
    int argc;
    char **argv;
    char *input_path;
    char *output_path;
    pid_t pid;
    int type;
    int status;
    struct process *next;
};

struct job
{
    int id;
    struct process *root;
    char *command;
    pid_t pgid;
    int mode;
};

struct shell_info
{
    char cur_user[TOKEN_BUFSIZE];
    char cur_dir[PATH_BUFSIZE];
    char pw_dir[PATH_BUFSIZE];
    struct job *jobs[NR_JOBS + 1];
    char *history[MAX_HISTORY];
};

struct shell_info *shell;

#endif



