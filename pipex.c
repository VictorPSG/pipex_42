/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 23:10:47 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/08 17:35:10 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	create_file(char *argv[])
{
	int	outfile;

	if (argv[4] == NULL)
		return (0);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		return (0);
	return (outfile);
}

static int	is_valid_input(int argc, char *argv[])
{
	int	infile;

	if (argc != 5)
	{
		ft_putstr_fd("Uso: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (0);
	}
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
	{
		perror("infile");
		return (0);
	}
	return (infile);
}

int	main(int argc, char *argv[], char *envp[])
{
	static int	fd[2];
	int			outfile;
	int			infile;

	outfile = create_file(argv);
	infile = is_valid_input(argc, argv);
	if (!infile)
		return (0);
	if (!outfile)
	{
		perror("outfile");
		return (0);
	}
	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	child_process_one(fd, argv, envp, infile);
	child_process_two(fd, argv, envp, outfile);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
