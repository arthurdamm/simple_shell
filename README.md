# simple shell
### Overview
`simple shell` is a C module that behaves like sh. This project was developed as part of the third month curriculum at [Holberton School](https://www.\holbertonschool.com/), San Francisco.
### Usage
* Includes shell.h
* compile using `gcc -Wall -Werror -Wextra -pedantic *.c`
* Once in the shell, use exactly like sh. A list of covered features is provided below.
* Function returns with the specified exit status.

### Features
`simple shell` handles command line input, including arguements. In addition to standard commands, the following features are currently implemented.

|  Builtin Commands  |    Functionality                            |
| ------------------ | ------------------------------------------- |
| `exit [status]`    | Exit shell with specified exit status       |
| `env`              | Print list of current environment variables |

|  Other Actions     |    Functionality                            |
| ------------------ | ------------------------------------------- |
| `Ctrl-D`           | End of file - exit shell                    |

### Example Usage
* `ls -l`
* `exit 98`
### Release History
* 0.0.1
  * Work in progress
### About
All files were created and compiled on `Ubuntu 14.04.4 LTS` using `GCC 4.8.4` with the following flags: `-Wall -Werror -Wextra -pedantic`
### Authors
[Jason Cortella](https://github.com/jasoncortella) - [@JasonCortella](https://twitter.com/JasonCortella) \|\| [Arthur Damm](https://github.com/arthurdamm) - [@arthurdamm](https://twitter.com/arthurdamm)