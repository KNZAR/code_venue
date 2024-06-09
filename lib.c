// a "safer" input function
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAILED_ALLOCATING NULL
#define REALLOC_FAILURE -1
#define FAILED_TRIMMING -2

/* returns null if allocation for string fails, returns uncompleted string if array resizing fails
   returns string with extra memory blocks if trimming fails, signals user with error pointer
*/
char* input(const char* prompt, int *error)
{
    *error = 0;
    // checks if prompt is empty string or null
    if((prompt != NULL && strcmp(prompt, "") != 0))
        printf("%s", prompt);


    int mut_buffer = 10;
    int char_count = 0;
    char c;
    char *str = malloc(sizeof(char) * mut_buffer);
    {
        free(str);
        return FAILED_ALLOCATING;
    }

    if(str == NULL)
        return NULL;

    // reads from terminal until there a newline character or there is no more data to read
    while((c = fgetc(stdin)) != '\n' && c != EOF)
    {
        // checks if the string will be full next iteration
        if(char_count == mut_buffer - 1)
        {
            mut_buffer *= 2;

            // copy pointer if original pointer is lost if realloc fails
            char *cp = str;
            
            // resize array
            str = realloc(str, sizeof(char) * mut_buffer);

            // returns string midway typing if failed to resize
            if(str == NULL)
            {
                *error = REALLOC_FAILURE;
                return cp;

            }
        }
        // adds most recently read character
        str[char_count] = c;
        char_count++;
    }

    // terminates our string
    str[char_count] = '\0';
    
    // string with exact length without extra memory from realloc calls
    char* trimmed_str = malloc(sizeof(char) * (char_count + 1));

    // returns string with extra memory if malloc fails
    if(trimmed_str == NULL)
    {
        *error = FAILED_TRIMMING;
        return str;
    }
    strcpy(trimmed_str, str);
    free(str);

    return trimmed_str;
}

