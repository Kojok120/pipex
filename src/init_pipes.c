/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokamoto <kojokamo120@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:08:35 by kokamoto          #+#    #+#             */
/*   Updated: 2025/01/13 20:08:43 by kokamoto         ###   ########.fr       */
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
		write(2, "Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n", 49);
		write(2, "   or: ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn outfile\n",
			58);
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
