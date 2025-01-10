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

#ifndef PARSE_H
#define PARSE_H

#define MAX_PATH_SIZE 120
#define MAX_CMD_SIZE 120
#define MAX_ARGS_SIZE 120
#define MAX_PROG_SIZE 120
#define MAX_HOST_SIZE 120

void parse_command(char *command);




#endif /* PARSE_H */
