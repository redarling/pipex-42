/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <asyvash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:31:22 by asyvash           #+#    #+#             */
/*   Updated: 2024/03/17 11:08:40 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *msg)
{
	perror(msg);
	exit(1);
}

void	ft_free(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i] != NULL)
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

static void	child_process(char **argv, char **envp, int fd[2])
{
	int	file_in;

	file_in = open(argv[1], O_RDONLY, 0777);
	if (file_in == -1)
		ft_error("File");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("dup2");
	if (dup2(file_in, STDIN_FILENO) == -1)
		perror("dup2");
	close(fd[0]);
	close(file_in);
	ft_execute_cmd(argv[2], envp);
}

static void	parent_process(char **argv, char **envp, int fd[2])
{
	int	file_out;

	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_out == -1)
		ft_error("File");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror("dup2");
	if (dup2(file_out, STDOUT_FILENO) == -1)
		perror("dup2");
	close(fd[1]);
	close(file_out);
	ft_execute_cmd(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		ft_error("It must be executed as:\n./pipex file1 cmd1 cmd2 file2");
	if (pipe(fd) == -1)
		ft_error("Pipe");
	pid = fork();
	if (pid == -1)
		ft_error("Fork");
	if (pid == 0)
		child_process(argv, envp, fd);
	if (waitpid(pid, NULL, 0) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		ft_error("Waitpid");
	}
	if (pid != 0)
		parent_process(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
