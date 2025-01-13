/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokamoto <kojokamo120@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:55:53 by kokamoto          #+#    #+#             */
/*   Updated: 2025/01/13 15:56:08 by kokamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
