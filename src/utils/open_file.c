/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:13:20 by dsagong           #+#    #+#             */
/*   Updated: 2025/09/17 14:17:41 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "utils.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int	open_input_file(char *filename)
{
	int	fd;

	if (!filename)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_error(filename, strerror(errno));
		return (-1);
	}
	return (fd);
}

int	open_output_file(char *filename, int append_mode)
{
	int	fd;
	int	flags;

	if (!filename)
		return (-1);
	flags = O_WRONLY | O_CREAT;
	if (append_mode)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		print_error(filename, strerror(errno));
		return (-1);
	}
	return (fd);
}
