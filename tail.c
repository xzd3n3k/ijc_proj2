#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LEN 4095

struct BUFFER
{
    int buf;
    int start;
    int end;
    char **lines;
} typedef BUFFER;

BUFFER * cb_create(int n) {
    BUFFER *buffer = malloc(sizeof(BUFFER));
    buffer->start=0;
    buffer->end=0;
    buffer->buf=n;

    buffer->lines=malloc(n*sizeof(char *));

    if (!buffer->lines) {
        fprintf(stderr, "Internal error allocing space for buffer!");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        buffer->lines[i] = malloc(MAX_LINE_LEN*sizeof(char));
        if (!buffer->lines[i])
        {
            fprintf(stderr, "Internal error allocing space for line in buffer!");
            exit(1);
        }
    }
    
    return buffer;
}

void cb_put(BUFFER *cb, char *line) {
    strcpy((cb->lines)[cb->end++], line);
    cb->end %= cb->buf;
}

char *cb_get(BUFFER *cb) {
    char *line = (cb->lines)[cb->start++];
    cb->start %= cb->buf;

    return line;
}

void cb_free(BUFFER *cb) {
    free(cb);
}

int main(int argc, char *argv[]) {
    int arg_idx = 1;
    int num_lines = 10;
    FILE *file;

    if (argc < 1 || argc > 4) {
        fprintf(stderr, "Wrong number of arguments, expected up to 3 arguments, got %d", argc-1);
        return 1;
    }
    
    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        if (argc < 3) {
            printf("Error: -n option requires an argument\n");
            return 1;
        }

    num_lines = atoi(argv[2]);
    arg_idx += 2;
    }

    if (arg_idx >= argc) {
        file = stdin;
    } else {
        file = fopen(argv[arg_idx], "r");
        if (file == NULL) {
            printf("Error: could not open file %s\n", argv[arg_idx]);
            return 1;
        }
    }

    char line[MAX_LINE_LEN];
    int line_len;
    BUFFER *buffer = cb_create(num_lines);

    if (buffer == NULL) {
        fprintf(stderr, "Error allocating memory for buffer!");
        return 1;
    }

    while (fgets(line, MAX_LINE_LEN, file) != NULL)
    {
        line_len = strlen(line);
        
        if (line_len > MAX_LINE_LEN - 1) {
            fprintf(stderr, "Warning! Line is too long. Cutting off excess characters!");
            line_len = MAX_LINE_LEN - 1;
            line[line_len] = '\0';
        }

        cb_put(buffer, line);
    }

    if (file != stdin) {
        fclose(file);
    }

    for (int i = 0; i < num_lines; i++)
    {
        char *line = cb_get(buffer);
        printf("%s", line);
    }

    cb_free(buffer);
    
    

    return 0;
}
