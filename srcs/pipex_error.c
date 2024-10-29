/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:07:09 by jaoh              #+#    #+#             */
/*   Updated: 2024/10/29 12:35:39 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_error_argc(int ac)
{
	dup2(ERR, OUT);
	ft_printf("%s: Invalid number of arguments, %d is given\n", P_NAME, ac - 1);
	exit(1);
}

void	pipex_error_pipe(int err_no)
{
	dup2(ERR, OUT);
	ft_printf("%s: %s\n", P_NAME, strerror(err_no));
	exit(2);
}

void	pipex_error_open(int err_no, char *file)
{
	dup2(ERR, OUT);
	ft_printf("%s: %s: %s\n", P_NAME, strerror(err_no), file);
}

void	pipex_error_fork(int err_no)
{
	dup2(ERR, OUT);
	ft_printf("%s: %s\n", P_NAME, strerror(err_no));
	exit(4);
}

void	pipex_error_write(int err_no, char *file, char *line)
{
	if (line)
		free(line);
	dup2(ERR, OUT);
	ft_printf("%s: %s: %s\n", P_NAME, strerror(err_no), file);
	exit(5);
}
