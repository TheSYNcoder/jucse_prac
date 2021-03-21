#ifndef UTILS_H
#define UTILS_H

#include "main.h"

int get_job_id_by_pid( int pid);
struct job* get_job_by_id( int id);
int get_pgid_by_job_id(int id);
int get_next_job_id();
int wait_for_pid( int pid);
int wait_for_job( int id);
int print_processes_of_job(int id); 
int print_job_status(int id);
int set_job_status(int id, int status);
int set_process_status(int pid, int status);
int is_job_completed(int id);
int insert_job(struct job *job);
int remove_job(int id);
int release_job(int id);
int get_proc_count(int id, int filter);


#endif