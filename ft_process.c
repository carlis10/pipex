/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:45:25 by cravegli          #+#    #+#             */
/*   Updated: 2024/03/14 14:24:50 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd(char *cmd, char **envp)
{
	char	*res;
	int		i;

	i = 0;
	while (envp[i])
	{
		res = ft_strjoin(envp[i], "/");
		res = ft_strjoin(res, cmd);
		if (access(res, 0) == 0)
			return (res);
		free(res);
		i++;
	}
	return (NULL);
}

void	child_process(t_pipex *pip, char **argv, int pipe[2], char **envp)
{
	char	*cmd;
	char	**commands;

	if (dup2(pip->in_file, 0) == -1)
		ft_error("dup error");
	if (dup2(pipe[1], 1) == -1)
		ft_error("dup error");
	close(pipe[0]);
	close(pip->out_file);
	commands = ft_split(argv[2], ' ');
	if (!commands[0])
		ft_error("no commands");
	cmd = get_cmd(commands[0], pip->path);
	if (!cmd)
	{
		ft_free_pipe(pip);
		ft_error("invalid command");
	}
	execve(cmd, commands, envp);
}

void	parent_process(t_pipex *pip, char **argv, int pipe[2], char **envp)
{
	char	*cmd;
	char	**commands;

	waitpid(pip->parent, NULL, 0);
	if (dup2(pip->out_file, 1) == -1)
		ft_error("dup error");
	if (dup2(pipe[0], 0) == -1)
		ft_error("dup error");
	close(pipe[1]);
	close(pip->in_file);
	commands = ft_split(argv[3], ' ');
	if (!commands[0])
		ft_error("no commands");
	cmd = get_cmd(commands[0], pip->path);
	if (!cmd)
	{
		ft_free_pipe(pip);
		ft_error("invalid command");
	}
	execve(cmd, commands, envp);
}
