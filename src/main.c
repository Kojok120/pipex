/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokamoto <kokamoto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:36:50 by kokamoto          #+#    #+#             */
/*   Updated: 2025/01/09 20:14:53 by kokamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_for_children(t_pipex *px)
{
	int	i;

	i = 0;
	while (i < px->cmd_count)
	{
		waitpid(px->pids[i], NULL, 0);
		i++;
	}
	free(px->pids);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;
	int		i;

	init_pipes(&px, argc, argv, envp);
	create_pipes(&px);
	i = 0;
	while (i < px.cmd_count)
	{
		px.pids[i] = fork();
		if (px.pids[i] == -1)
			error_exit("Fork error");
		if (px.pids[i] == 0)
		{
			if (i == 0)
				handle_first_cmd(&px);
			else if (i == px.cmd_count - 1)
				handle_last_cmd(&px, i);
			else
				handle_middle_cmd(&px, i);
		}
		i++;
	}
	close_pipes(&px);
	wait_for_children(&px);
	return (0);
}
