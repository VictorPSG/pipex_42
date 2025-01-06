// #include "pipex.h"
// #include <fcntl.h>


// int main(int argc, char *argv[])
// {
// 	char 	*path1;
// 	char 	*path2;
// 	char 	**cmd1;
// 	char 	*teste[4];
// 	char 	*teste1[4];
// 	pid_t	pid1;
// 	pid_t	pid2;
// 	int		fd[2];
// 	int 	file_fd;
// 	char 	**cmd2;
	
// 	pipe(fd);
// 	file_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	// int	fd;
// 	if (argc <= 3)
// 	{
// 		ft_putstr_fd("Número de argumentos inválido!\n", 1);
// 		return (1);
// 	}
// 	cmd1 = ft_split(argv[2], ' ');
// 	cmd2 = ft_split(argv[3], ' ');
// 	if (!cmd1)
// 	{
// 		ft_putstr_fd("Erro ao dividir comando!\n", 1);
// 		return (1);
// 	}
// 	path1 = ft_strjoin(PATH, cmd1[0]);
// 	path2 = ft_strjoin(PATH, cmd2[0]);
// 	if (!path1)
// 	{
// 		ft_putstr_fd("Erro ao alocar path!\n", 1);
// 		return (1);
// 	}
// 	teste[0] = cmd1[0];
// 	teste[1] = argv[1];
// 	teste[2] = cmd1[1];
// 	teste[3] = NULL;
// 	printf("Teste[1]: %s\n", cmd1[0]);

// 	teste1[1] = argv[1];
// 	teste1[2] = cmd2[1];
// 	teste1[3] = NULL;

// 	pid1 = fork();
// 	if(pid1 == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		if (execv(path1, teste) == -1)
// 		{
// 			perror("execv falhou");
// 		}
// 	teste1[0] = cmd2[0];
// 		printf("saklddsklafn");
// 	}
// 	pid2 = fork();
// 	if(pid2 == 0)
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 			execv(path2, teste1);
// 		printf("\n\n\n\n\n\n\nkjbjk\n\n\n\n\n\n\n");
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);

// 	return (0);
// }
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

int main(int argc, char *argv[], char *envp[])
{
    int fd[2];
    pid_t pid1, pid2;
    int infile, outfile;

    if (argc != 5)
    {
        ft_putstr_fd("Uso: ./pipex infile cmd1 cmd2 outfile\n", 2);
        return (1);
    }
    if (pipe(fd) == -1)
        return (perror("pipe"), 1);
    infile = open(argv[1], O_RDONLY);
    if (infile < 0)
        return (perror("infile"), 1);
    outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile < 0)
        return (perror("outfile"), 1);
    pid1 = fork();
    if (pid1 == 0)
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
    pid2 = fork();
    if (pid2 == 0)
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
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);
}
