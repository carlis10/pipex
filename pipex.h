/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cravegli <cravegli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:27:03 by cravegli          #+#    #+#             */
/*   Updated: 2024/07/03 13:20:26 by cravegli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		in_file;
	int		out_file;
	char	**path;
	int		pipe[2];
	pid_t	parent;
}				t_pipex;

void	ft_error(char *msg);
void	child_process(t_pipex *pip, char **argv, int pipe[2], char **envp);
void	parent_process(t_pipex *pip, char **argv, int pipe[2], char **envp);
void	ft_free_pipe(t_pipex *pip);
void	ft_close_pipes(int pipe[2]);
void	ft_free_split(char **map);

#endif