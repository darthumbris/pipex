/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 11:27:18 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/17 16:02:38 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

char	**get_path_str(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 5))
			return (ft_split(ft_substr(envp[i], 5, ft_strlen(envp[i])), ':'));
		i++;
	}
	return (NULL);
}

char	**get_cmd_arg(char *argv)
{
	char	**cmd_args;

	cmd_args = ft_split(argv, ' ');
	return (cmd_args);
}

void	command_exec(char **paths, char **cmd_args, char **envp)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], ft_strjoin("/", cmd_args[0]));
		execve(cmd_path, cmd_args, envp);
		free(cmd_path);
		i++;
	}
}
