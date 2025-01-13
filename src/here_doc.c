/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokamoto <kojokamo120@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:44:05 by kokamoto          #+#    #+#             */
/*   Updated: 2025/01/13 16:15:05 by kokamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_here_doc(char *limiter)
{
	char	*line;
	int		pip[2];

	if (pipe(pip) == -1)
		error_exit("Pipe error");
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		printf("line: %s", line);
		printf("limiter: %s", limiter);
		if (line <= 0)
			exit(1);
		printf("ft_strcmp: %d\n", ft_strcmp(line, limiter));
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		write(pip[1], line, ft_strlen(line));
		write(pip[1], "\n", 1);
		free(line);
	}
	printf("here_doc.c dup2: %d\n",pip[0]);
	if (dup2(pip[0], STDIN_FILENO) == -1)
		error_exit("Dup2 error");
	close(pip[0]);
	close(pip[1]);
}

