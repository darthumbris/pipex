/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/17 15:43:56 by shoogenb      #+#    #+#                 */
/*   Updated: 2021/12/17 16:34:48 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * Parent process reads from fd[0]
 * and writes to outfile fd created by the 
 * pipe function;
 * to this it needs to use dup2 to change
 * the stdin to end[0] and stdout to outfile fd
 */
void	parent_process(int outfile_fd, char **cmd2, char **envp)
{
	int		done;
	char	*path;

	path = get_path_str(envp);
	waitpid(-1, &done, 0);
	dup2(outfile_fd, STDIN_FILENO);
	dup2(fd[0], STDOUT_FILENO);
	close(fd[1]);
	close(outfile_fd);
	execve();
}

/*
 * Child process reads from the infile fd
 * and writes to fd[1] created by the 
 * pipe function;
 * to this it needs to use dup2 to change
 * the stdin to infile fd and stdout to fd[1]
 */
void	child_process(int infile_fd, char **cmd1, char **envp)
{
	char	*path;

	path = get_path_str(envp);
	dup2(infile_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(infile_fd);
	execve();
}

char	*get_path_str(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

/*
 * fd[0] is the parent process and this process reads
 * fd[1] is the child process and this process writes
 * the child process has to be executed first
 * that's why it gets cmd1 and parent process
 * gets cmd2 (command 2)
 */
void	pipex(int infile_fd, int outfile_fd, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];
	char	**cmd1;
	char	**cmd2;

	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	pipe(fd);
	pid = fork();
	if (pid < 0)
		return (perror("FORK: "));
	if (!pid)
		parent_process(outfile_fd, cmd2, envp);
	else
		child_process(infile_fd, cmd1, envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		infile_fd;
	int		outfile_fd;

	outfile_fd = open(argv[4], O_WRONLY | O_APPEND | O_CREAT, 0644);
	infile_fd = open(argv[1], O_RDONLY);
	if (outfile_fd < 0 || infile_fd < 0)
		return (-1);
	pipex(infile_fd, outfile_fd, argv, envp);
	return (0);
}
