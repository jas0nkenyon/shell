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

#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include <unistd.h>
#include <pwd.h>

#define MAX_CMD_SIZE 120
#define MAX_PATH_SIZE 120
 
/* Configure argument parser
 *
 *
*/
const char *argp_program_version = "shell version 1.0";
const char *argp_program_bug_address = "<jas0nkenyon@protonmail.com>";
static char doc[] = "A simple shell built with C";
static char args_doc[] = "ARG1 ARG2";
static struct argp_option options[] = {
  {"interactive", 'i', 0, 0, "Run shell interactively (this is probably what you want to use)", 0},
  {"verbose", 'v', 0, 0, "Produce verbose output", 0},
  {"quiet", 'q', 0, 0, "Don't produce any output", 0},
  {"silent", 's', 0, OPTION_ALIAS, 0, 0},
  {"output", 'o', "FILE", 0, "Output to FILE instead of standard output", 0 },
  { 0 }
};

/* Used by main to communicate with parse_opt. 
 *
 *
*/
struct arguments
{
//  char *args[3];                /* arg1 & arg2 */
    int silent, verbose, interactive;
    char *output_file;
};


/* Parse a single option. */
static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
    know is a pointer to our arguments structure. */
    struct arguments *arguments = state->input;

    switch (key)
    {
        case 'i':
	    arguments->interactive = 1;
	    break;
        case 'q': case 's':
            arguments->silent = 1;
            break;
        case 'v':
            arguments->verbose = 1;
            break;
        case 'o':
            arguments->output_file = arg;
            break;
/*
        case ARGP_KEY_ARG:
            if (state->arg_num >= 2)
                argp_usage (state);
                arguments->args[state->arg_num] = arg;
                break;
        case ARGP_KEY_END:
            if (state->arg_num < 2)
                argp_usage (state);
                break;
*/

        default:
            return ARGP_ERR_UNKNOWN;
}
    return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc, 0, 0, 0};




int main(int argc, char **argv)
{
    struct arguments arguments;
    /* Default values. */
    arguments.silent = 0;
    arguments.verbose = 0;
    arguments.output_file = "-";
    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    
/* Main loop for interactive mode
 *
 *
 */
    if (arguments.interactive)
    {
       printf("You are running %s in interactive mode. Enter Ctrl-D to exit.\n", argp_program_version);
       while(1)
       {

/* Get user information for shell prompt
 *
 *
*/ 
           struct passwd *passwd = getpwuid(getuid());
           char cwd[MAX_PATH_SIZE];
           getcwd(cwd, MAX_PATH_SIZE);
           printf("[%s@%s]$ ", passwd->pw_name, cwd);
           char input[MAX_CMD_SIZE];

           /* Check for EOF from stdin*/
           if(!fgets(input, MAX_CMD_SIZE, stdin))
	       return 0;     
       }

     }



    return 0;
}
