/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:17:31 by dsagong           #+#    #+#             */
/*   Updated: 2025/09/15 16:19:54 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "herdoc.h"
#include <stdlib.h>

static int	detect_quotes(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}

static size_t	get_len_without_quotes(char *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		if (*str != '\'' && *str != '"')
			len++;
		str++;
	}
	return (len);
}

static void	copy_without_quotes(char *dest, char *src)
{
	while (*src)
	{
		if (*src != '\'' && *src != '"')
			*dest++ = *src;
		src++;
	}
	*dest = '\0';
}

t_delim_info	make_delim(char *raw)
{
	t_delim_info	info;

	info.cooked_delim = malloc(get_len_without_quotes(raw) + 1);
	if (!info.cooked_delim)
		return (info);
	info.quoted_flag = detect_quotes(raw);
	copy_without_quotes(info.cooked_delim, raw);
	return (info);
}
