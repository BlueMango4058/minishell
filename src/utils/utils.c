/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:05:55 by jechoi            #+#    #+#             */
/*   Updated: 2025/09/17 14:24:39 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_redirect_token(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT \
		|| type == T_APPEND || type == T_HEREDOC);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	si;

	i = 0;
	si = 0;
	while (dest[i] != '\0')
		i++;
	while (src[si] != '\0')
	{
		dest[i] = src[si];
		i++;
		si++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_dirname(const char *path)
{
	char	*result;
	char	*last_slash;
	int		len;

	if (!path || !*path)
		return (ft_strdup("."));
	result = ft_strdup(path);
	if (!result)
		return (NULL);
	len = ft_strlen(result);
	while (len > 1 && result[len - 1] == '/')
	{
		result[len - 1] = '\0';
		len--;
	}
	if (ft_strcmp(result, "/") == 0)
		return (result);
	last_slash = ft_strrchr(result, '/');
	if (!last_slash)
		return (free(result), ft_strdup("."));
	if (last_slash == result)
		return (result[1] = '\0', result);
	*last_slash = '\0';
	return (result);
}
