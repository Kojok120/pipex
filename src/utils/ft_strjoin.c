/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokamoto <kokamoto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:57:56 by kokamoto          #+#    #+#             */
/*   Updated: 2025/01/08 23:00:05 by kokamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*array;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	array = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (array == NULL)
		return (NULL);
	ft_strlcpy(array, s1, ft_strlen(s1)+ 1);
	ft_strlcpy(array + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (array);
}
