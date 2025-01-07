/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 20:30:26 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/06 21:26:32 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	path_env = NULL;
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i] || !(path_env = envp[i] + 5))
		return (NULL);
	if (!(paths = ft_split(path_env, ':')))
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

int	child_process_one(int fd[2], char *argv[], char *envp[], int infile)
{
	pid_t	pid;
	char	*cmd1_path;
	char	**cmd1_args;

	pid = fork();
	if (pid == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		cmd1_path = get_command_path(ft_split(argv[2], ' ')[0], envp);
		cmd1_args = ft_split(argv[2], ' ');
		execve(cmd1_path, cmd1_args, envp);
		perror("execve cmd1");
		exit(1);
	}
	return (fd);
}

int	child_process_two(int fd[2], char *argv[], char *envp[], int outfile)
{
	pid_t	pid;
	char *cmd2_path;
	char **cmd2_args;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		cmd2_path = get_command_path(ft_split(argv[3], ' ')[0], envp);
		char **cmd2_args = ft_split(argv[3], ' ');
		execve(cmd2_path, cmd2_args, envp);
		perror("execve cmd2");
		exit(1);
	}
	return (fd);
}