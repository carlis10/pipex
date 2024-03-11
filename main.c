/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:40:03 by cravegli          #+#    #+#             */
/*   Updated: 2024/03/11 15:46:57 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_envp(char **envp)
{
	int		i;
	char	**res;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			res = ft_split(envp[i] + 5, ':');
		i++;
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

	pip.path = ft_get_envp(envp);
	if (!envp)
		ft_error("env error");
	pip.in_file = open(argv[1], O_RDONLY);
	if (!pip.in_file)
		ft_error("infile error");
	pip.out_file = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (!pip.out_file)
		ft_error("outfile error");
	if (pipe(pip.pipe) != 0)
		ft_error("pipe error");
	pip.parent = fork();
	if (pip.parent < 0)
		ft_error("fork error");
	if (!pip.parent)
		child_process(&pip, argv, pip.pipe, envp);
	if (pip.parent)
		parent_process(&pip, argv, pip.pipe, envp);
	ft_free_pipe(&pip);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		ft_error("arg error");
	ft_pipex(argv, envp);
	return (0);
}
