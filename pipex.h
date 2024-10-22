/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:54:04 by jaoh              #+#    #+#             */
/*   Updated: 2024/10/22 08:13:20 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "./libft/libft.h"

# define READ_END 0
# define WRITE_END 1

enum e_pipex_error
{
	END = 1,
	CMD_NOT_FOUND = 0,
	NO_FILE = -1,
	NO_PERM = -2,
	INV_ARGS = -3,
	NO_MEMORY = -4,
	PIPE_ERR = -5,
	DUP_ERR = -6,
	FORK_ERR = -7,
	NO_PATH = -8,
	CMD_FAIL = -9
};

typedef struct s_pipexdata
{
	int		in_fd;
	int		out_fd;
	char	**env_path;
	int		here_doc;
	t_list	*cmds;
}				t_pipexdata;

typedef struct s_pipexcmd
{
	char	*full_path;
	char	**cmd;
}				t_pipexcmd;

t_list		*pipex_lstnew(char *full_path, char **cmd);

void		pipex_freecmd(void *node);

int			find_command(t_pipexdata *data, char *cmd, char **full_path);

t_list		*parse_commands(int argc, char **argv, t_pipexdata *data);

t_pipexdata	*pipex_get_data(int argc, char **argv, int here_doc, char **envp);

void		pipex_perror(char *param, int err);

void		*pipex_exit(t_pipexdata *data, char *param, int err, char ***cmd);

void		*pipex(t_pipexdata *data, char **envp);

#endif
