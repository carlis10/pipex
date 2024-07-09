/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:07:08 by cravegli          #+#    #+#             */
/*   Updated: 2024/07/03 13:20:21 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_pipe(t_pipex *pip)
{
	int	i;

	i = 0;
	close(pip->in_file);
	close(pip->out_file);
	ft_close_pipes(pip->pipe);
	while (pip->path[i])
	{
		free(pip->path[i]);
		i++;
	}
	free(pip->path);
}

void	ft_free_split(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free (map);
}
