/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_unix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:07:01 by jaoh              #+#    #+#             */
/*   Updated: 2024/10/29 12:35:37 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_dup(int fd, int fd_new)
{
	dup2(fd, fd_new);
	close(fd);
}

void	ft_free_all(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	ft_do_pipe(char *cmd, char **env)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		pipex_error_pipe(errno);
	pid = fork();
	if (pid == -1)
		pipex_error_fork(errno);
	if (!pid)
	{
		close(fd[0]);
		ft_close_dup(fd[1], OUT);
		if (ft_exec(cmd, env) < 0)
			exit(6);
		return ;
	}
	close(fd[1]);
	ft_close_dup(fd[0], IN);
}

void	ft_do_fork(char *cmd, char **env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		pipex_error_fork(errno);
	if (!pid)
	{
		if (ft_exec(cmd, env) < 0)
			exit(6);
		return ;
	}
	close(IN);
	close(OUT);
}

void	pipex_error_cmd(char *path, int err_no)
{
	dup2(ERR, OUT);
	if (ft_bad_path(path) == 1)
		ft_printf("%s: %s: %s\n", P_NAME, strerror(err_no), path);
	else
		ft_printf("%s: command not found: %s\n", P_NAME, path);
}
