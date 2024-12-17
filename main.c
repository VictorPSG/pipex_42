#include "pipex.h"
#include <fcntl.h>


int main(int argc, char *argv[])
{
	char 	*path1;
	char 	*path2;
	char 	**cmd1;
	char 	*teste[4];
	char 	*teste1[4];
	// int		fd[2];
	int 	file_fd;
	char 	**cmd2;

	file_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// int	fd;
	dup2(file_fd, 1);
	if (argc <= 2)
	{
		ft_putstr_fd("Número de argumentos inválido!\n", 1);
		return (1);
	}
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	if (!cmd1)
	{
		ft_putstr_fd("Erro ao dividir comando!\n", 1);
		return (1);
	}
	path1 = ft_strjoin(PATH, cmd1[0]);
	path2 = ft_strjoin(PATH, cmd2[0]);
	if (!path1)
	{
		ft_putstr_fd("Erro ao alocar path!\n", 1);
		return (1);
	}
	teste[0] = cmd1[0];
	teste[1] = argv[1];
	teste[2] = cmd1[1];
	teste[3] = NULL;
	printf("Teste[1]: %s\n", cmd1[0]);
	if (execv(path1, teste) == -1)
	{
		perror("execv falhou");
	}
	teste1[0] = cmd2[0];
	teste1[1] = argv[1];
	teste1[2] = cmd2[1];
	teste1[3] = NULL;

	execv(path2, teste1);
	close(file_fd);
	return (0);
}
