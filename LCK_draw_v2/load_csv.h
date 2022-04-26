#ifndef LOAD_CSV_H
#define LOAD_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "team_struct.h"

#pragma warning(disable:4996) // scanf오류 전처리기

#define MAX_DATA 4

struct data {
    char s[MAX_DATA][1024];
};

void remove_spaces(char* s) {
    const char* d = s;
    do {
        while (*d == ' ') {
            ++d;
        }
    } while (*s++ = *d++);
}

void getfield(char* line, struct data* d, int end_idx)
{
    int idx = 0;

    char* token = strtok(line, ",");

    do
    {
        //printf("token: %s\n", token);
        strcpy(d->s[idx++], token);
    } while (idx != end_idx && (token = strtok(NULL, ",")));

}

void print(Team* team, char path[])
{
    FILE* stream = fopen(path, "r");
    int i = 0;
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        struct data d;

        char temp[50] = "\"";
        char* tmp = strdup(line);
        getfield(tmp, &d, MAX_DATA);

        //printf("%s\t\t\t%s\t\t\t%s\t\t\t%s\n", d.s[0], d.s[1], d.s[2], d.s[3]);
        if (i != 0)
        {
            strcat(temp, team->name);
            strcat(temp, "\"");

            if (!strcmp(temp, d.s[0]))
            {
                team->pre_GP += atoi(d.s[1]);
                team->pre_win += atoi(d.s[2]);
            }
        }

        free(tmp);
        i++;
    }
}

#endif // !LOAD_CSV_H