/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:53:38 by dsagong           #+#    #+#             */
/*   Updated: 2025/09/17 14:24:16 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "output.h"
#include "utils.h"

static char	*create_env_string(t_envp *current)
{
	size_t	key_len;
	size_t	val_len;
	char	*env_str;

	key_len = ft_strlen(current->key);
	val_len = ft_strlen(current->value);
	env_str = malloc(key_len + val_len + 2);
	if (!env_str)
		return (NULL);
	ft_strcpy(env_str, current->key);
	ft_strcat(env_str, "=");
	ft_strcat(env_str, current->value);
	return (env_str);
}

static int	envp_list_length(t_envp *envp_list)
{
	int		count;
	t_envp	*current;

	count = 0;
	current = envp_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static char	**allocate_env_array(int size)
{
	char	**array;

	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	array[size] = NULL;
	return (array);
}

static int	fill_env_array(char **array, t_envp *envp_list)
{
	int		i;
	t_envp	*current;

	i = 0;
	current = envp_list;
	while (current)
	{
		array[i] = create_env_string(current);
		if (!array[i])
		{
			while (i > 0)
				free(array[--i]);
			free(array);
			return (0);
		}
		i++;
		current = current->next;
	}
	return (1);
}

char	**env_list_to_array(t_envp *envp_list)
{
	int		size;
	char	**array;

	if (!envp_list)
		return (NULL);
	size = envp_list_length(envp_list);
	array = allocate_env_array(size);
	if (!array)
		return (NULL);
	if (!fill_env_array(array, envp_list))
		return (NULL);
	return (array);
}
