/* A simple shell made with C
 * Copyright (C) 2025 Jason Kenyon
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/* Standard library */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* My includes from ./includes */
#include "parse.h"

void parse_command (char *command)
{
    /* Remove trailing newline from `fgets` */
    command[strcspn(command, "\n")] = '\0';
    char *args[MAX_ARGS_SIZE];
    	
    /* Unpack input for use with `execvp` and builtins */
    char *current = strtok(command, " ");
    args[0] = current; 
    int i = 1;
    while (current != NULL)
    {
	current = strtok(NULL, " ");
	args[i++] = current;
    }

    /* Check for the `exit` command from the user */
    if (strcmp(args[0], "exit") == 0)
        exit(EXIT_SUCCESS);

/* Handling of shell builtins such as `cd`
 * For now, `cd` is very basic
 *
 */
    else if (strcmp(args[0], "cd") == 0)
    {
	if (args[1] == NULL)
	    chdir(getenv("HOME"));
        chdir(args[1]);
    }

/* Execution of binaries specified by the user
 * 
 *
 */
    else
    {
        /* Fork process and execute specified command `command` using `execvp` */
        pid_t pid = fork();
        if (pid == -1)
        {
            /* In case we cannot fork the process */
            fprintf(stderr, "Failed to fork current process PID %d\n", getpid());
        } 
        else if (pid > 0)
        {
            /* Wait for `execvp` to return */
            int status;
            waitpid(pid, &status, 0);
        }
        else 
        {
            execvp(args[0], args);

            /* In case `execvp` fails */
            fprintf(stderr, "Failed to execute command %s as process PID %d\n", args[0], getpid());
            exit(EXIT_FAILURE);
        }
    }
}




