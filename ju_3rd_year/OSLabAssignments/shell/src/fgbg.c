#include "fgbg.h"

int command_fg(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("usage: fg <pid>\n");
        return -1;
    }

    int status;
    pid_t pid;
    int job_id = -1;

    if (argv[1][0] == '%')
    {
        job_id = atoi(argv[1] + 1);
        pid = get_pgid_by_job_id(job_id);
        if (pid < 0)
        {
            printf("shell: fg %s: no such job\n", argv[1]);
            return -1;
        }
    }
    else
    {
        pid = atoi(argv[1]);
    }

    if (kill(-pid, SIGCONT) < 0)
    {
        printf("shell: fg %d: job not found\n", pid);
        return -1;
    }

    tcsetpgrp(0, pid);

    if (job_id > 0)
    {
        set_job_status(job_id, STATUS_CONTINUED);
        print_job_status(job_id);
        if (wait_for_job(job_id) >= 0)
        {
            remove_job(job_id);
        }
    }
    else
    {
        wait_for_pid(pid);
    }

    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(0, getpid());
    signal(SIGTTOU, SIG_DFL);

    return 0;
}

int command_bg(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("usage: bg <pid>\n");
        return -1;
    }

    pid_t pid;
    int job_id = -1;

    if (argv[1][0] == '%')
    {
        job_id = atoi(argv[1] + 1);
        pid = get_pgid_by_job_id(job_id);
        if (pid < 0)
        {
            printf("mysh: bg %s: no such job\n", argv[1]);
            return -1;
        }
    }
    else
    {
        pid = atoi(argv[1]);
    }

    if (kill(-pid, SIGCONT) < 0)
    {
        printf("mysh: bg %d: job not found\n", pid);
        return -1;
    }

    if (job_id > 0)
    {
        set_job_status(job_id, STATUS_CONTINUED);
        print_job_status(job_id);
    }

    return 0;
}