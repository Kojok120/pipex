/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojok <kojok@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:41:34 by kokamoto          #+#    #+#             */
/*   Updated: 2025/03/26 06:04:37 by kojok            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_exit(char *msg)
{
	perror(msg);
	exit(1);
}

void	error_exit_msg(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(1);
}
