/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokamoto <kokamoto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:49:13 by kokamoto          #+#    #+#             */
/*   Updated: 2025/01/08 22:59:17 by kokamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	countwords(char const *s, char c)
{
	int	i;
	int	count;
	int	n;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			n = 0;
			count++;
			while (s[i + n] && s[i + n] != c)
				n++;
			i += n - 1;
		}
		i++;
	}
	return (count);
}

static char	*ft_strndup(char const *src, int n)
{
	int		i;
	char	*array;

	array = (char *)malloc((n + 1) * sizeof(char));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		array[i] = src[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}

static char	**ft_split2(char const *s, char c, char **array, int i)
{
	int	j;
	int	n;

	j = 0;
	while (s[++i])
	{
		if (s[i] != c)
		{
			n = 0;
			while (s[i + n] && s[i + n] != c)
				n++;
			array[j] = ft_strndup(&s[i], n);
			if (array[j] == NULL)
			{
				while (j > 0)
					free(array[--j]);
				free(array);
				return (NULL);
			}
			i += n - 1;
			j++;
		}
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (s == NULL)
		return (NULL);
	array = (char **)malloc((countwords(s, c) + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	return (ft_split2(s, c, array, -1));
}
