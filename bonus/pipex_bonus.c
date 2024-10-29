/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:05:47 by jaoh              #+#    #+#             */
/*   Updated: 2024/10/29 12:33:26 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

int	ft_init_here_doc(char *file, char *eof)
{
	int		fd;
	char	*limiter;
	char	*line;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	limiter = ft_strjoin(eof, "\n");
	line = get_next_line(IN);
	while (line)
	{
		if (!strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		if (write(fd, line, ft_strlen(line)) < 0)
			pipex_error_write(errno, file, line);
		free(line);
		line = get_next_line(IN);
	}
	free(limiter);
	close(fd);
	return (open(file, O_RDONLY));
}

int	ft_init_inout(int *fd_in, int *fd_out, int ac, char **av)
{
	int	i;

	if (!strcmp(av[1], "here_doc"))
	{
		*fd_in = ft_init_here_doc(av[1], av[2]);
		*fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		i = 3;
	}
	else
	{
		*fd_in = open(av[1], O_RDONLY);
		*fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		i = 2;
	}
	if (*fd_in == -1)
		pipex_error_open(errno, av[1]);
	if (*fd_out == -1)
		pipex_error_open(errno, av[ac - 1]);
	return (i);
}

static void	ft_false_inout(int *index, int mode)
{
	int	fd[2];

	if (pipe(fd) == -1)
		pipex_error_pipe(errno);
	if (mode == 0)
	{
		ft_close_dup(fd[0], IN);
		close(fd[1]);
		*index += 1;
	}
	else
	{
		ft_close_dup(fd[1], OUT);
		close(fd[0]);
		*index += 1;
	}
}

static void	ft_check_inout(int fd_in, int fd_out, int *start, int *rep)
{
	if (fd_in == -1)
		ft_false_inout(start, 0);
	else
		ft_close_dup(fd_in, IN);
	*rep = *start;
	if (fd_out == -1)
		ft_false_inout(rep, 1);
	else
		ft_close_dup(fd_out, OUT);
}

int	main(int ac, char *av[], char **env)
{
	int	fd_in;
	int	fd_out;
	int	i;
	int	j;

	if (ac < 5 || (!strcmp(av[1], "here_doc") && ac < 6))
		pipex_error_argc(ac);
	i = ft_init_inout(&fd_in, &fd_out, ac, av);
	ft_check_inout(fd_in, fd_out, &i, &j);
	while (i < ac - 2)
		ft_do_pipe(av[i++], env);
	if (fd_out != -1)
		ft_do_fork(av[i], env);
	while (j++ < ac - 1)
		wait(NULL);
	if (!ft_strcmp(av[1], "here_doc"))
		unlink(av[1]);
	return (0);
}
