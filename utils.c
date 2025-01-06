/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:30:26 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/02 03:07:23 by victda-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex.h"

char *get_command_path(char *cmd, char **envp)
{
    char *path_env = NULL;
    char **paths;
    char *full_path;
    int i = 0;

    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
        i++;
    if (!envp[i] || !(path_env = envp[i] + 5))
		return (NULL);
	if(!(paths = ft_split(path_env, ':')))
		return (NULL);
    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
        if (access(full_path, X_OK) == 0)
            return (full_path);
        free(full_path);
        i++;
    }
    return (NULL);
}

int child_process_one(int fd[2], char *argv[], char *envp[], int infile)
{
	pid_t	pid;

	pid = fork();
    if (pid == 0)
    {
        dup2(infile, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        char *cmd1_path = get_command_path(ft_split(argv[2], ' ')[0], envp);
        char **cmd1_args = ft_split(argv[2], ' ');
        execve(cmd1_path, cmd1_args, envp);
        perror("execve cmd1");
        exit(1);
    }
	return (fd);
}

int child_process_two(int fd[2], char *argv[], char *envp[], int outfile)
{	
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		char *cmd2_path = get_command_path(ft_split(argv[3], ' ')[0], envp);
		char **cmd2_args = ft_split(argv[3], ' ');
		execve(cmd2_path, cmd2_args, envp);
		perror("execve cmd2");
		exit(1);
	}
	return (fd);
}