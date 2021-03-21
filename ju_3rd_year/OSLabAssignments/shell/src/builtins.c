// #include "main.h"
#include "builtins.h"



int command_mkdir( int argc, char **argv){

    if ( argc < 2 ){
        printf("usage: mkdir <directory_name>\n");
        return -1;
    }

    struct stat st ={0};

    if ( stat(argv[1], &st) == -1) {
        mkdir(argv[1], 0700);
    }

    return 0;
}

int command_man( int argc , char **argv){
    int i;
    for ( i=0; i < 40; i++ )
    printf("*");
    printf("\n\n");

    printf("\t----- MAN ----- \n\n");
    printf("BUILTIN COMMANDS AVAILABLE : \n\n");
    printf("mkdir : used to make a new directory \n");
    printf("\t Usage : mkdir dir1 dir2 dir3 ...\n\n");

    printf("info : used to show file specific information of a particular file \n");
    printf("\t Usage : mkdir dir1 dir2 dir3 ...\n\n");

    printf("edit : used to launch vim editor or edit an existing file \n");
    printf("\t Usage : edit ?<file>\n\n");

    printf("exitshell : used to exit the shell \n");
    printf("\t Usage : exitshell \n\n");

    for (i = 0; i < 40; i++)
        printf("*");
    printf("\n\n");
}


int command_edit( int argc, char **argv){

    pid_t childpid = fork();

    int background =0;

    
    if ( argc > 2 && argv[2] != NULL && strcmp(argv[2], "&") == 0 ){
        background=1;
        argv[2]=NULL;
    }

    if ( !background && argc==2 && strcmp(argv[1],"&") == 0){
        background=1;
        argv[1]=NULL;
    }

    if (childpid < 0){
        printf("Shell : Child forking failed\n");
        return -1;
    }

    // current process : child and is a background process
    else if ( childpid == 0 && background){
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        int x = open("/dev/null", O_RDWR );
        dup(x);

        argv[0]="vi";
        if ( execv("/usr/bin/vi" , argv) == -1){
            printf("usage: edit ?<file>\n");
            return -1;
        }
        kill(getpid() , SIGINT);
    }


    // current process to be launched in the foreground
    else if ( !childpid && !background){

        argv[0]="vi";
        if ( execv("/usr/bin/vi" , argv) == -1){
            printf("usage: edit ?<file>\n");
            return -1;
        }
        return 0;
    }

    else if( !background){

        // wait for parent process to terminate
        wait(NULL);
        return -1;
    }
    return 0;



    
    
}

int command_info( int argc , char **argv) {
    if ( argc != 2){
        printf("usage: info <filename>\n");
        return -1;
    }

    struct stat stats ={0};

    if ( stat( argv[1], &stats) == 0 ){
        // file permissions
        printf("\nFile access : ");
        if ( stats.st_mode & R_OK)
            printf("read ");
        if ( stats.st_mode & W_OK)
            printf("write ");
        if ( stats.st_mode & X_OK)
            printf("execute ");

        printf("\nFile Size: %lld" , stats.st_size);

        struct tm dt;

        // File creation
        dt = *(gmtime(&stats.st_ctime));
        printf("\nCreated on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
               dt.tm_hour, dt.tm_min, dt.tm_sec);

        // File modification time
        dt = *(gmtime(&stats.st_mtime));
        printf("\nModified on: %d-%d-%d %d:%d:%d\n", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
               dt.tm_hour, dt.tm_min, dt.tm_sec);

        return 0;
    }
    else{
        printf("File %s does not exist\n", argv[1]);
        return -1;
    }
    return 0;
}


int command_exitshell( int argc , char **argv){
    if ( argc >= 2){
        printf("Usage: exitshell\n");
        return -1;
    }
    printf("Goodbye :) \n");
    exit(0);
}


