/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojok <kojok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:08:35 by kokamoto          #+#    #+#             */
/*   Updated: 2025/03/26 06:09:49 by kojok            ###   ########.fr       */
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
		px->limiter = ft_strjoin(argv[2], "\n");
	}
	if (!px->here_doc && argc < 5)
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n", 49);
		write(2, "   or: ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn outfile\n",
			59);
		exit(1);
	}
	px->cmd_count = argc - 3 - px->here_doc;
	px->pids = (pid_t *)malloc(sizeof(pid_t) * px->cmd_count);
	if (!px->pids)
		perror_exit("Malloc error");
}

void	create_pipes(t_pipex *px)
{
	int	i;

	px->pipes = (int **)malloc(sizeof(int *) * (px->cmd_count - 1));
	if (!px->pipes)
		perror_exit("Malloc error");
	i = 0;
	while (i < px->cmd_count - 1)
	{
		px->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!px->pipes[i])
			perror_exit("Malloc error");
		if (pipe(px->pipes[i]) == -1)
			perror_exit("Pipe error");
		i++;
	}
}
