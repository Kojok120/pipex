/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokamoto <kokamoto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:36:46 by kokamoto          #+#    #+#             */
/*   Updated: 2025/01/09 20:14:53 by kokamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../src/utils/utils.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define BUFFER_SIZE 4096

typedef struct s_pipex
{
	int		cmd_count;
	int		here_doc;
	char	*limiter;
	char	**argv;
	char	**envp;
	int		**pipes;
	pid_t	*pids;
}			t_pipex;

void		error_exit(char *msg);
void		init_pipes(t_pipex *px, int argc, char **argv, char **envp);
void		create_pipes(t_pipex *px);
void		close_pipes(t_pipex *px);
void		handle_here_doc(char *limiter);
char		*get_cmd_path(char *cmd, char **envp);
void		execute_cmd(char *cmd, char **envp);
int			handle_first_cmd(t_pipex *px);
void		handle_middle_cmd(t_pipex *px, int i);
void		handle_last_cmd(t_pipex *px, int i);

#endif