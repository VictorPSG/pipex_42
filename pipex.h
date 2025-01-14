/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:59:43 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/08 17:48:00 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>

char	*get_command_path(char *cmd, char **envp);
int		*child_process_one(int fd[2], char *argv[], char *envp[], int infile);
int		*child_process_two(int fd[2], char *argv[], char *envp[], int outfile);
#endif