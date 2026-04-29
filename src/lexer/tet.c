#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *line;

    while (1)
    {
        line = readline("minishell$ ");
        if (!line) // Ctrl+D
            break;

        if (*line)           // don't save empty command
            add_history(line);

        printf("You entered: %s\n", line);

        free(line);
    }
    return 0;
}