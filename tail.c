#include <stdio.h>
#define MAX_LINE_LEN 4095

struct BUFFER
{
    int buf;
    int start;
    int end;
    char **lines;
} typedef BUFFER;

BUFFER * cb_create(int n) {
    BUFFER *buffer = calloc(sizeof(BUFFER));
    buffer->start=0;
    buffer->end=0;
    buffer->buf=n;

    buffer->lines=calloc(n*sizeof(char *));

    if (!buffer->lines) {
        fprintf(stderr, "Internal error allocing space for buffer!");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        buffer->lines[i] = calloc(MAX_LINE_LEN*sizeof(char));
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
    char *line = *(cb->lines)[cb->start++];
    cb->start %= cb->buf;

    return line;
}

void cb_free(BUFFER *cb) {
    free(cb);
}

int main() {
    
    return 0;
}
