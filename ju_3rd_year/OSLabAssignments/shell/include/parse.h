#ifndef PARSE_H
#define PARSE_H

#include "main.h"

struct process* shell_parse_command_segment( char *command);
struct job* shell_parse_command( char *line);
char* read_line();
char* helper_strtrim(char * line);
int get_command_type( char *command );

#endif
