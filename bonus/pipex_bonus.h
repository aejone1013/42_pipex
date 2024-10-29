/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:30:59 by jaoh              #+#    #+#             */
/*   Updated: 2024/10/29 12:33:28 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# define OUT STDOUT_FILENO
# define IN STDIN_FILENO
# define ERR STDERR_FILENO
# define P_NAME "pipex"

int		ft_init_fd(int *fd_in, int *fd_out, int argc, char **argv);
int		ft_init_here_doc(char *file, char *eof);
void	ft_close_dup(int fd, int new_fd);
void	ft_free_all(char **array);
void	ft_do_pipe(char *cmd, char **envp);
void	ft_do_fork(char *cmd, char **envp);

int		ft_exec(char *argv, char **envp);
int		ft_bad_path(char *file);
char	*ft_get_path(char *file, char **envp);
char	**ft_get_allpath(char **envp);

void	pipex_error_argc(int argc);
void	pipex_error_pipe(int err_no);
void	pipex_error_open(int err_no, char *file);
void	pipex_error_fork(int err_no);
void	pipex_error_write(int err_no, char *file, char *line);
void	pipex_error_cmd(char *path, int err_no);

#endif
