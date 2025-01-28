/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokamoto <kojokamo120@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:42:06 by kokamoto          #+#    #+#             */
/*   Updated: 2025/01/28 14:16:47 by kokamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_cmd_path(char **envp)
{
	char	**paths;

	// int		i;

	while (*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (!*envp)
		return (NULL);
	paths = ft_split(*envp + 5, ':');
	// i = 0;
	// while (paths[i])
	// {
	// 	part_path = ft_strjoin(paths[i], "/");
	// 	path = ft_strjoin(part_path, cmd);
	// 	free(part_path);
	// 	if (access(path, F_OK | X_OK) == 0)
	// 		return (path);
	// 	free(path);
	// 	i++;
	// }
	// return (NULL);
	return (paths);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path = NULL;
		char	**paths;
	int i;
	char	*path;
	char	*part_path;

	cmd_args = ft_split(cmd, ' ');
	// cmd_argsの中身を表示.heredocの場合これはoutput.txtに入っちゃう。
	// printf("cmd_args: %s\n", cmd_args[0]);
	paths = get_cmd_path(envp);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd_args[0]);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
		{	cmd_path = path;
			break;
		}
		free(path);
		i++;
	}

	if (!cmd_path)
		error_exit("Command not found");
	if (execve(cmd_path, cmd_args, envp) == -1)
		error_exit("Execve error");
}

void	handle_first_cmd(t_pipex *px)
{
	int	infile;

	if (px->here_doc)
		handle_here_doc(px->limiter);
	else
	{
		infile = open(px->argv[1], O_RDONLY);
		if (infile == -1)
			error_exit("Infile error");
		if (dup2(infile, STDIN_FILENO) == -1)
			error_exit("Dup2 error");
		close(infile);
	}
	//here_docだと下のが入っちゃう
	// printf("first_cmd");
	if (dup2(px->pipes[0][1], STDOUT_FILENO) == -1)
		error_exit("Dup2 error");
	close(px->pipes[0][0]);
	close(px->pipes[0][1]);
	execute_cmd(px->argv[2 + px->here_doc], px->envp);
}

void	handle_middle_cmd(t_pipex *px, int i)
{
	if (dup2(px->pipes[i - 1][0], STDIN_FILENO) == -1)
		error_exit("Dup2 error");
	if (dup2(px->pipes[i][1], STDOUT_FILENO) == -1)
		error_exit("Dup2 error");
	close(px->pipes[i - 1][0]);
	close(px->pipes[i - 1][1]);
	close(px->pipes[i][0]);
	close(px->pipes[i][1]);
	execute_cmd(px->argv[i + 2 + px->here_doc], px->envp);
}

void	handle_last_cmd(t_pipex *px, int i)
{
	int	outfile;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (px->here_doc)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	outfile = open(px->argv[px->cmd_count + 2 + px->here_doc], flags, 0644);
	if (outfile == -1)
		error_exit("Outfile error");
	if (dup2(px->pipes[i - 1][0], STDIN_FILENO) == -1)
		error_exit("Dup2 error");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		error_exit("Dup2 error");
	close(px->pipes[i - 1][0]);
	close(px->pipes[i - 1][1]);
	close(outfile);
	execute_cmd(px->argv[i + 2 + px->here_doc], px->envp);
}
