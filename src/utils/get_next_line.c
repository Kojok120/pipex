/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokamoto <kojokamo120@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:07:19 by kokamoto          #+#    #+#             */
/*   Updated: 2025/01/13 14:58:56 by kokamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*init_memory(char **memo)
{
	char	*memory;

	if (!*memo)
		*memo = ft_strdup("");
	memory = (char *)malloc(BUFFER_SIZE + 1);
	if (!memory)
		return (NULL);
	return (memory);
}

char	*read_line(int fd, char **memo)
{
	char	*buf;
	ssize_t	ret;
	char	*temp;

	buf = init_memory(memo);
	if (!buf)
		return (NULL);
	ret = 1;
	while (!ft_strchr(*memo, '\n') && ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
		{
			free(buf);
			free(*memo);
			*memo = NULL;
			return (NULL);
		}
		buf[ret] = '\0';
		temp = ft_strjoin(*memo, buf);
		free(*memo);
		*memo = temp;
	}
	free(buf);
	return (*memo);
}

char	*extract_line(char **memo)
{
	char	*line;
	char	*temp;

	if (!ft_strchr(*memo, '\n'))
	{
		if (**memo == '\0')
		{
			free(*memo);
			*memo = NULL;
			return (NULL);
		}
		line = ft_strdup(*memo);
		free(*memo);
		*memo = NULL;
	}
	else
	{
		line = ft_substr(*memo, 0, ft_strchr(*memo, '\n') - *memo + 1);
		temp = ft_strdup(ft_strchr(*memo, '\n') + 1);
		free(*memo);
		*memo = temp;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*memo[OPEN_MAX];

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_line(fd, &memo[fd]) == NULL)
		return (NULL);
	return (extract_line(&memo[fd]));
}
