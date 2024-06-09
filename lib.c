#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* input(const char* prompt)
{
    // checks if prompt is empty string or null
    if(strcmp(prompt, "") != 0 && prompt != NULL)
        printf("%s", prompt);


    int mut_buffer = 10;
    int char_count = 0;
    char c;
    char *str = malloc(sizeof(char) * mut_buffer);
    if(str == NULL)
        return NULL;

    // reads from terminal until there a newline character or there is no more data to read
    while((c = fgetc(stdin)) != '\n' && c != EOF)
    {
        // checks if the string will be full next iteration
        if(char_count == mut_buffer - 1)
        {
            mut_buffer += 10;

            // copy pointer if original pointer is lost if realloc fails
            char *cp = str;
            // increase size of string by 10
            str = realloc(str, sizeof(char) * mut_buffer);

            // realloc failure
            if(str == NULL)
            {
                free(cp);
                return NULL;
            }
        }
        // adds most recently read character
        str[char_count] = c;
        char_count++;
    }

    // terminates our string
    str[char_count] = '\0';
    int str_length = strlen(str);
    
    // string with exact length without extra memory from realloc calls
    char* trimmed_str = malloc(sizeof(char) * (str_length + 1));
    if(trimmed_str == NULL)
    {
        free(str);
        return NULL;
    }
    strcpy(trimmed_str, str);
    free(str);

    return trimmed_str;
}

