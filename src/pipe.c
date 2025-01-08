/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokamoto <kokamoto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:43:05 by kokamoto          #+#    #+#             */
/*   Updated: 2025/01/08 23:16:05 by kokamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipes(t_pipex *px)
{
	int	i;

	px->pipes = (int **)malloc(sizeof(int *) * (px->cmd_count - 1));
	if (!px->pipes)
		error_exit("Malloc error");
	i = 0;
	while (i < px->cmd_count - 1)
	{
		px->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!px->pipes[i])
			error_exit("Malloc error");
		if (pipe(px->pipes[i]) == -1)
			error_exit("Pipe error");
		i++;
	}
}

void	close_pipes(t_pipex *px)
{
	int	i;

	i = 0;
	while (i < px->cmd_count - 1)
	{
		close(px->pipes[i][0]);
		close(px->pipes[i][1]);
		free(px->pipes[i]);
		i++;
	}
	free(px->pipes);
}
