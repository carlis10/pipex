/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:45:25 by cravegli          #+#    #+#             */
/*   Updated: 2024/07/09 12:59:11 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd(char *cmd, char **envp)
{
	char	*res;
	char	*aux;
	int		i;

	i = 0;
	if (access(cmd, 0) == 0)
		return (cmd);
	while (envp[i])
	{
		aux = ft_strjoin(envp[i], "/");
		res = ft_strjoin(aux, cmd);
		free(aux);
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

	commands = ft_split(argv[2], ' ');
	if (!commands[0])
		ft_error("no commands\n");
	cmd = get_cmd(commands[0], pip->path);
	if (!cmd)
	{
		ft_free_pipe(pip);
		free(cmd);
		ft_free_split(commands);
		ft_error("invalid command\n");
	}
	if (dup2(pip->in_file, 0) == -1)
		ft_error("dup error\n");
	if (dup2(pipe[1], 1) == -1)
		ft_error("dup error\n");
	close(pipe[0]);
	close(pip->out_file);
	execve(cmd, commands, envp);
	ft_free_split(commands);
}

void	parent_process(t_pipex *pip, char **argv, int pipe[2], char **envp)
{
	char	*cmd;
	char	**commands;

	waitpid(pip->parent, NULL, 0);
	commands = ft_split(argv[3], ' ');
	if (!commands[0])
		ft_error("no commands\n");
	cmd = get_cmd(commands[0], pip->path);
	if (!cmd)
	{
		ft_free_pipe(pip);
		ft_free_split(commands);
		ft_error("invalid command\n");
	}
	if (dup2(pip->out_file, 1) == -1)
		ft_error("dup error\n");
	if (dup2(pipe[0], 0) == -1)
		ft_error("dup error\n");
	close(pipe[1]);
	close(pip->in_file);
	execve(cmd, commands, envp);
	ft_free_split(commands);
}
