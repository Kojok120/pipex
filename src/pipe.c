/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokamoto <kokamoto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:43:05 by kokamoto          #+#    #+#             */
/*   Updated: 2025/01/09 20:14:53 by kokamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipes(t_pipex *px, int argc, char **argv, char **envp)
{
	px->argv = argv;
	px->envp = envp;
	px->here_doc = 0;
	if (argc >= 6 && !ft_strcmp(argv[1], "here_doc"))
	{
		px->here_doc = 1;
		px->limiter = argv[2];
	}
	if (!px->here_doc && argc < 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n", 47);
		write(2, "   or: ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn outfile\n",
			57);
		exit(1);
	}
	px->cmd_count = argc - 3 - px->here_doc;
	px->pids = (pid_t *)malloc(sizeof(pid_t) * px->cmd_count);
	if (!px->pids)
		error_exit("Malloc error");
}

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
