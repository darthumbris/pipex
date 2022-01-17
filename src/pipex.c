/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/17 15:43:56 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/17 16:05:12 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * child process cmd2 reads from fd[0]
 * and writes to outfile fd created by the 
 * pipe function;
 * to this it needs to use dup2 to change
 * the stdin to end[0] and stdout to outfile fd
 */
void	child_process_cmd2(int outfile_fd, char **argv, char **envp, int fd[2])
{
	char	**paths;
	char	**cmd_args;

	paths = get_path_str(envp);
	dup2(outfile_fd, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(outfile_fd);
	cmd_args = get_cmd_arg(argv[3]);
	command_exec(paths, cmd_args, envp);
	ft_putstr_fd(cmd_args[0], 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

/*
 * Child process cmd1 reads from the infile fd
 * and writes to fd[1] created by the 
 * pipe function;
 * to this it needs to use dup2 to change
 * the stdin to infile fd and stdout to fd[1]
 */
void	child_process_cmd1(int infile_fd, char **argv, char **envp, int fd[2])
{
	char	**paths;
	char	**cmd_args;

	paths = get_path_str(envp);
	dup2(infile_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(infile_fd);
	cmd_args = get_cmd_arg(argv[2]);
	command_exec(paths, cmd_args, envp);
	ft_putstr_fd(cmd_args[0], 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

/*
 * 
 */
void	pipex(int infile_fd, int outfile_fd, char **argv, char **envp)
{
	pid_t	child1_pid;
	pid_t	child2_pid;
	int		fd[2];
	int		done;

	pipe(fd);
	child1_pid = fork();
	if (child1_pid < 0)
		return (perror("FORK: "));
	if (child1_pid == 0)
		child_process_cmd1(infile_fd, argv, envp, fd);
	child2_pid = fork();
	if (child2_pid < 0)
		return (perror("FORK: "));
	if (child2_pid == 0)
		child_process_cmd2(outfile_fd, argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(child1_pid, &done, 0);
	waitpid(child2_pid, &done, 0);
	exit(WEXITSTATUS(done));
}

int	main(int argc, char **argv, char **envp)
{
	int		infile_fd;
	int		outfile_fd;

	if (argc != 5)
	{
		ft_putendl_fd("error: ambiguous redirect", 2);
		return (1);
	}
	outfile_fd = open(argv[4], O_WRONLY | O_APPEND | O_CREAT, 0644);
	infile_fd = open(argv[1], O_RDONLY);
	if (outfile_fd < 0 || infile_fd < 0)
	{
		if (outfile_fd > 2)
			close(outfile_fd);
		else
			perror(argv[4]);
		if (infile_fd > 2)
			close(infile_fd);
		else
			perror(argv[1]);
		return (EXIT_FAILURE);
	}
	pipex(infile_fd, outfile_fd, argv, envp);
	return (0);
}
