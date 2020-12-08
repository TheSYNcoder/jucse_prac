#include "main.h"
#include "parse.h"
#include "launch.h"
#include "utils.h"
#include "builtins.h"
#include "fgbg.h"
#include "utils.c"
#include "launch.c"
#include "builtins.c"
#include "fgbg.c"
#include "parse.c"




void sigint_handler(int signal)
{
    printf("\n");
}

void shell_print_start()
{
    printf("\n");
    printf(" ________  ________  ________  _______                  ___  ___  ___       \n");
    printf("|\\   __  \\|\\   ____\\|\\   ____\\|\\  ___ \\                |\\  \\|\\  \\|\\  \\    \n");
    printf("\\ \\  \\|\\ /\\ \\  \\___|\\ \\  \\___|\\ \\   __/|   ____________\\ \\  \\ \\  \\ \\  \\    \n");
    printf(" \\ \\   __  \\ \\  \\    \\ \\_____  \\ \\  \\_|/__|\\____________\\ \\  \\ \\  \\ \\  \\   \n");
    printf("  \\ \\  \\|\\  \\ \\  \\____\\|____|\\  \\ \\  \\_|\\ \\|____________|\\ \\  \\ \\  \\ \\  \\  \n");
    printf("   \\ \\_______\\ \\_______\\____\\_\\  \\ \\_______\\              \\ \\__\\ \\__\\ \\__\\  \n");
    printf("    \\|_______|\\|_______|\\_________\\|_______|               \\|__|\\|__|\\|__|\n");
    printf("                       \\|_________|                                            \n");
    printf("                                                                               \n");
    printf("                                                                               \n");
    printf("\n\n");
}

void shell_update_cwd_info()
{
    getcwd(shell->cur_dir, sizeof(shell->cur_dir));
}

void shell_init()
{
    struct sigaction sigint_action = {
        .sa_handler = &sigint_handler,
        .sa_flags = 0};
    sigemptyset(&sigint_action.sa_mask);
    sigaction(SIGINT, &sigint_action, NULL);

    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);

    pid_t pid = getpid();
    setpgid(pid, pid);
    tcsetpgrp(0, pid);

    shell = (struct shell_info *)malloc(sizeof(struct shell_info));
    getlogin_r(shell->cur_user, sizeof(shell->cur_user));

    struct passwd *pw = getpwuid(getuid());
    strcpy(shell->pw_dir, pw->pw_dir);

    int i;
    for (i = 0; i < NR_JOBS; i++)
    {
        shell->jobs[i] = NULL;
    }

    shell_update_cwd_info();
}

void shell_print_promt()
{
    printf(COLOR_CYAN "%s" COLOR_NONE " in " COLOR_YELLOW "%s" COLOR_NONE "\n", shell->cur_user, shell->cur_dir);
    printf(COLOR_GREEN "syncShell>" COLOR_NONE " ");
}



void shell_loop()
{
    char *line;
    struct job *job;
    int status = 1;

    while (1)
    {
        shell_print_promt();
        line = read_line();
        if (strlen(line) == 0)
        {
            check_zombie();
            continue;
        }
        job = shell_parse_command(line);
        status = launch_job(job);
    }
}



int main(int argc, char **argv)
{
    shell_init();
    shell_print_start();
    shell_loop();

    return EXIT_SUCCESS;
}