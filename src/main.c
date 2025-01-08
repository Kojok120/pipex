/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokamoto <kokamoto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:36:50 by kokamoto          #+#    #+#             */
/*   Updated: 2025/01/08 23:15:31 by kokamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(t_pipex *px, int argc, char **argv, char **envp)
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

	init_pipex(&px, argc, argv, envp);
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
