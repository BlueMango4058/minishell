/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:57:07 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/17 18:30:43 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <sys/stat.h>
#include <errno.h>

static char	*join_path(char *dir, char *command)
{
	char	*full_path;
	int		dir_len;
	int		cmd_len;

	if (!dir || !command)
		return (NULL);
	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(command);
	full_path = malloc(dir_len + cmd_len + 2);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	if (dir[dir_len - 1] != '/')
	{
		full_path[dir_len] = '/';
		full_path[dir_len + 1] = '\0';
	}
	ft_strcat(full_path, command);
	return (full_path);
}

static void	free_array(char **dirs)
{
	int	i;

	i = -1;
	while (dirs[++i])
		free(dirs[i]);
	free(dirs);
}

static char	*search_in_path(char *command, char *path)
{
	char	**dirs;
	char	*full_path;
	int		i;

	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_path = join_path(dirs[i], command);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free_array(dirs);
			return (full_path);
		}
		if (full_path)
			free(full_path);
		i++;
	}
	free_array(dirs);
	return (NULL);
}

static int	access_process(char *command)
{
	struct stat	st;

	if (access(command, F_OK) != 0)
	{
		if (errno == ENOTDIR)
		{
			print_error(command, "Not a directory");
			g_exit_status = 126;
		}
		else
		{
			print_error(command, "No such file or directory");
			g_exit_status = 127;
		}
		return (FAILURE);
	}
	if (stat(command, &st) == 0 && S_ISDIR(st.st_mode))
		return (print_error(command, "Is a directory"), g_exit_status = 126, \
				FAILURE);
	if (access(command, X_OK) != 0)
		return (print_error(command, "Permission denied"), g_exit_status = 126, \
				FAILURE);
	return (SUCCESS);
}

char	*find_executable(char *command, t_shell *shell)
{
	char		*path_env;
	char		*executable;

	if (!command)
		return (NULL);
	if (ft_strchr(command, '/'))
	{
		if (access_process(command) == FAILURE)
			return (NULL);
		return (ft_strdup(command));
	}
	path_env = get_path_env(shell);
	if (!path_env)
	{
		g_exit_status = 127;
		return (NULL);
	}
	executable = search_in_path(command, path_env);
	if (!executable)
	{
		print_error(command, "command not found");
		g_exit_status = 127;
	}
	return (executable);
}
