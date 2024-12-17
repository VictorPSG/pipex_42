#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int file_fd;

    // Abre o arquivo em modo de escrita
    file_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_fd == -1)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Redireciona stdout (1) para o arquivo usando dup2
    if (dup2(file_fd, 1) == -1) // STDOUT_FILENO = 1
    {
        perror("Erro ao redirecionar stdout");
        return 1;
    }

    close(file_fd); // Fecha o descritor original, não é mais necessário

    // Tudo que for impresso agora será escrito no arquivo
	while(1)
	{
    	printf("Esta mensagem será escrita no arquivo 'output.txt'\n");
    	printf("Outra linha no arquivo!\n");
	}

    return 0;
}
