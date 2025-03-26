/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojok <kojok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:44:05 by kokamoto          #+#    #+#             */
/*   Updated: 2025/03/26 05:59:02 by kojok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_here_doc(char *limiter)
{
	char	*line;
	int		pip[2];

	if (pipe(pip) == -1)
		perror_exit("Pipe error");
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (line <= (char *)0)
			exit(1);
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		write(pip[1], line, ft_strlen(line));
		write(pip[1], "\n", 1);
		free(line);
	}
	if (dup2(pip[0], STDIN_FILENO) == -1)
		perror_exit("Dup2 error");
	close(pip[0]);
	close(pip[1]);
}
