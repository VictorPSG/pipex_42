/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:59:43 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/02 03:07:40 by victda-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
# define PATH "/usr/bin/"

int child_process(int fd[2], char *argv[], char *envp[]);
char *get_command_path(char *cmd, char **envp);
int child_process_one(int fd[2], char *argv[], char *envp[], int infile);
int child_process_two(int fd[2], char *argv[], char *envp[], int outfile);
#endif