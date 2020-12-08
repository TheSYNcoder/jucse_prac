#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>


// new folder
// edit file
// info 
// exit shell

int command_mkdir( int argc, char **argv);
int command_info( int arc, char **argv);
int command_edit(int argc, char **argv);
int command_exitshell( int argc, char **argv );
int command_man( int argc, char **argv);



#endif