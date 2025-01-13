/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokamoto <kojokamo120@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:10:19 by kokamoto          #+#    #+#             */
/*   Updated: 2025/01/13 14:58:03 by kokamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	ft_min(size_t i, size_t j)
{
	if (i <= j)
		return (i);
	else
		return (j);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*substr;

	i = 0;
	if (ft_strlen(s) < start)
		j = 0;
	else
		j = ft_strlen(s) - start;
	substr = (char *)malloc(ft_min(len, j) + 1);
	if (!substr)
		return (NULL);
	while (i < len && start < ft_strlen(s))
	{
		substr[i] = s[start];
		start++;
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
