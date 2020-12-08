
#include "parse.h"


int get_command_type( char* command ){
    if ( strcmp(command, "exitshell") == 0){
        return COMMAND_EXIT;
    }
    if ( strcmp(command , "mkdir") == 0 ){
        return COMMAND_MKDIR;
    }
    if ( strcmp(command , "info") == 0 ){
        return COMMAND_INFO;
    }
    if ( strcmp(command , "edit") == 0 ){
        return COMMAND_EDIT;
    }
    if ( strcmp(command , "fg") == 0 ){
        return COMMAND_FG;
    }
    if ( strcmp(command , "bg") == 0 ){
        return COMMAND_BG;
    }
    if ( strcmp(command, "man") == 0){
        return COMMAND_MAN;
    }
    return COMMAND_EXTERNAL;
}

char *helper_strtrim(char *line)
{
    char *head = line, *tail = line + strlen(line);

    while (*head == ' ')
    {
        head++;
    }
    while (*tail == ' ')
    {
        tail--;
    }
    *(tail + 1) = '\0';
    return head;
}

struct process *shell_parse_command_segment(char *segment)
{
    int bufsize = TOKEN_BUFSIZE;
    int position = 0;
    char *command = strdup(segment);
    char *token;
    char **tokens = (char **)malloc(bufsize * sizeof(char *));

    if (!tokens)
    {
        fprintf(stderr, "shell : allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(segment, TOKEN_DELIMITERS);
    while (token != NULL)
    {
        glob_t glob_buffer;
        int glob_count = 0;
        // if * or ? is present
        if (strchr(token, '*') != NULL || strchr(token, '?') != NULL)
        {
            glob(token, 0, NULL, &glob_buffer);

            // number of matches
            glob_count = glob_buffer.gl_pathc;
        }

        if (position + glob_count >= bufsize)
        {
            bufsize += TOKEN_BUFSIZE;
            bufsize += glob_count;
            tokens = (char **)realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "shell : allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        if (glob_count > 0)
        {
            int i;
            for (i = 0; i < glob_count; i++)
            {
                tokens[position++] = strdup(glob_buffer.gl_pathv[i]);
            }
            globfree(&glob_buffer);
        }
        else
        {
            tokens[position] = token;
            position++;
        }

        token = strtok(NULL, TOKEN_DELIMITERS);
    }

    int i = 0, argc = 0;
    char *input_path = NULL, *output_path = NULL;
    while (i < position)
    {
        if (tokens[i][0] == '<' || tokens[i][0] == '>')
        {
            break;
        }
        i++;
    }
    argc = i;

    for (; i < position; i++)
    {
        if (tokens[i][0] == '<')
        {
            if (strlen(tokens[i]) == 1)
            {
                input_path = (char *)malloc((strlen(tokens[i + 1]) + 1) * sizeof(char));
                strcpy(input_path, tokens[i + 1]);
                i++;
            }
            else
            {
                input_path = (char *)malloc(strlen(tokens[i]) * sizeof(char));
                strcpy(input_path, tokens[i] + 1);
            }
        }
        else if (tokens[i][0] == '>')
        {
            if (strlen(tokens[i]) == 1)
            {
                output_path = (char *)malloc((strlen(tokens[i + 1]) + 1) * sizeof(char));
                strcpy(output_path, tokens[i + 1]);
                i++;
            }
            else
            {
                output_path = (char *)malloc(strlen(tokens[i]) * sizeof(char));
                strcpy(output_path, tokens[i] + 1);
            }
        }
        else
        {
            break;
        }
    }

    for (i = argc; i <= position; i++)
    {
        tokens[i] = NULL;
    }

    struct process *new_proc = (struct process *)malloc(sizeof(struct process));
    new_proc->command = command;
    new_proc->argv = tokens;
    new_proc->argc = argc;
    new_proc->input_path = input_path;
    new_proc->output_path = output_path;
    new_proc->pid = -1;
    new_proc->type = get_command_type(tokens[0]);
    new_proc->next = NULL;
    return new_proc;
}

struct job *shell_parse_command(char *line)
{
    line = helper_strtrim(line);
    char *command = strdup(line);

    struct process *root_proc = NULL, *proc = NULL;
    char *line_cursor = line, *c = line, *seg;
    int seg_len = 0, mode = FOREGROUND_EXECUTION;

    if (line[strlen(line) - 1] == '&')
    {
        mode = BACKGROUND_EXECUTION;
        line[strlen(line) - 1] = '\0';
    }

    while (1)
    {
        if (*c == '\0' || *c == '|')
        {
            seg = (char *)malloc((seg_len + 1) * sizeof(char));
            strncpy(seg, line_cursor, seg_len);
            seg[seg_len] = '\0';

            struct process *new_proc = shell_parse_command_segment(seg);
            if (!root_proc)
            {
                root_proc = new_proc;
                proc = root_proc;
            }
            else
            {
                proc->next = new_proc;
                proc = new_proc;
            }

            if (*c != '\0')
            {
                line_cursor = c;
                while (*(++line_cursor) == ' ')
                    ;
                c = line_cursor;
                seg_len = 0;
                continue;
            }
            else
            {
                break;
            }
        }
        else
        {
            seg_len++;
            c++;
        }
    }

    struct job *new_job = (struct job *)malloc(sizeof(struct job));
    new_job->root = root_proc;
    new_job->command = command;
    new_job->pgid = -1;
    new_job->mode = mode;
    return new_job;
}

char *read_line()
{
    int bufsize = COMMAND_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer)
    {
        fprintf(stderr, "shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        c = getchar();

        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
        {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize)
        {
            bufsize += COMMAND_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer)
            {
                fprintf(stderr, "shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}


