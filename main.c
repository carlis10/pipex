/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:40:03 by cravegli          #+#    #+#             */
/*   Updated: 2024/07/09 14:06:07 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_try_access(char **argv)
{
	char	**commands;

	commands = ft_split(argv[2], ' ');
	if (access(commands[0], 0) != 0)
	{
		ft_free_split(commands);
		return (1);
	}
	ft_free_split(commands);
	commands = ft_split(argv[3], ' ');
	if (access(commands[0], 0) != 0)
	{
		ft_free_split(commands);
		return (1);
	}
	ft_free_split(commands);
	return (0);
}

char	**ft_get_envp(char **envp, char **argv)
{
	int		i;
	char	**res;

	i = 0;
	res = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			res = ft_split(envp[i] + 5, ':');
		i++;
	}
	if (!res)
	{
		if (ft_try_access(argv))
			ft_error("PATH error\n");
	}
	return (res);
}

void	ft_close_pipes(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}

void	ft_pipex(char **argv, char **envp)
{
	t_pipex	pip;

	pip.in_file = open(argv[1], O_RDONLY);
	if (pip.in_file < 0)
		ft_error("infile error\n");
	pip.out_file = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pip.out_file < 0)
		ft_error("outfile error\n");
	if (!envp[0])
	{
		if (ft_try_access(argv))
			ft_error("env error\n");
	}
	pip.path = ft_get_envp(envp, argv);
	if (pipe(pip.pipe) != 0)
		ft_error("pipe error\n");
	pip.parent = fork();
	if (pip.parent < 0)
		ft_error("fork error\n");
	if (!pip.parent)
		child_process(&pip, argv, pip.pipe, envp);
	if (pip.parent)
		parent_process(&pip, argv, pip.pipe, envp);
	ft_free_pipe(&pip);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		ft_error("arg error\n");
	ft_pipex(argv, envp);
	return (0);
}
