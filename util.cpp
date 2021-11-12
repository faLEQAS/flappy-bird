#include "util.hpp"
#include <stdlib.h>


int random(int min, int max)
{
    int range = max - min + 1;
    int num = rand() % range + min;
    return num;
}


char** split_str(char* str, char delimiter, int* len)
{
    (*len) = 0;
    char** arr = (char**)malloc(sizeof(char*)*(*len));
    char c;
    int prev = 0;
    for (int i = 0; true; i++)
    {
        c = str[i];
        if (c == delimiter || c == '\0')
        {
            (*len)++;
            arr = (char**)realloc(arr, sizeof(char*)*(*len));
            char* s = (char*)malloc(sizeof(char)*((i-prev)));
            for (int j = prev, k = 0; j < i; j++, k++)
            {
                s[k] = str[j];
            }
            s[(i-prev)] = '\0';
            prev = i+1;
            arr[(*len)-1] = s;
            if (c == '\0')
            {
                break;
            }
        }
    }
    return arr;
}

char* fgetline(FILE* fp)
{
    if (feof(fp))
    {
        return nullptr;
    }
    int len = 1;
    char* s = (char*)malloc(sizeof(char)*len);
    for (char c = fgetc(fp); c != EOF && c != '\n'; c = fgetc(fp))
    {
        len++;
        s = (char*)realloc(s, sizeof(char)*len);
        s[len-2] = c;
    }
	s[len-1] = '\0';
    return s;
}