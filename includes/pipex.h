/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 10:36:26 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/01/17 16:00:24 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

char	**get_path_str(char **envp);
char	**get_cmd_arg(char *argv);
void	command_exec(char **paths, char **cmd_args, char **envp);

#endif