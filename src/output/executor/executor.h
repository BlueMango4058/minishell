/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoi <jechoi@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:30:29 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/19 10:45:31 by jechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <signal.h>
# include "types.h"
# include "builtins.h"
# include "utils.h"
# include "global.h"

# define READ_END 0
# define WRITE_END 1

int		execute_pipeline(t_cmd *commands, t_shell *shell);
int		execute_builtin(t_cmd *cmd, t_shell *shell);
int		execute_external(t_cmd *cmd, t_shell *shell);
char	*find_executable(char *command, t_shell *shell);
pid_t	fork_process(void);
int		wait_for_children(pid_t *pids, int count);
void	setup_child_process(t_cmd *cmd, int *pipe_fds, \
		int cmd_index, int cmd_count);
void	setup_parent_process(int *pipe_fds, int cmd_index, int cmd_count);
void	close_all_pipes(int *pipe_fds, int pipe_count);
int		count_commands(t_cmd *cmd);
int		setup_redirections(t_cmd *cmd);
int		input_file_process(t_file *file);
int		single_cmd(t_cmd *commands, t_shell *shell);
int		create_pipes(int **pipe_fds, int cmd_count);
int		util_create_pipes(int **pipe_fds, int cmd_count);
void	print_signal(int exit_status);

#endif
