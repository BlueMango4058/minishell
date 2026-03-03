/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:30:53 by dsagong           #+#    #+#             */
/*   Updated: 2025/09/15 16:33:06 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void	check_fd_valid(int fd)
{
	if (fcntl(fd, F_GETFD) == -1)
		printf("FD %d is INVALID (errno=%d: %s)\n", fd, errno, strerror(errno));
	else
		printf("FD %d is VALID\n", fd);
}

// void	print_fd_content(int fd)
// {
// 	char	buf[1024];
// 	ssize_t	n;

// 	printf("***********HEREDOC LIST**********\n");
// 	printf("[heredoc fd: %d]\n", fd);
// 	while ((n = read(fd, buf, sizeof(buf) - 1)) > 0)
// 	{
// 		buf[n] = '\0';
// 		printf("%s", buf);
// 	}
// 	printf("\n----------------------------\n");
// }
