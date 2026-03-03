/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:51:37 by dsagong           #+#    #+#             */
/*   Updated: 2025/12/08 11:28:41 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "types.h"
# include "libft.h"
# include <stdio.h>

int		is_space(char c);
int		is_operator(char c);
int		is_quote(char c);
int		is_redir_type(t_token_type type);
int		is_valid_expand(t_exp *exp_data, char *value);
int		has_whitespace(const char *s);

char	*charjoin_and_free(char *s, char c);
int		is_redirect_token(t_token_type type);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_dirname(const char *path);
char	*ft_strcat(char *dest, const char *src);

int		init_shell(t_shell *shell);
char	**env_list_to_array(t_envp *envp_list);
void	free_env_list(t_envp *head);
void	free_env_array(char **env_array);
void	cleanup_shell(t_shell *shell);
void	print_error(char *cmd, char *msg);

int		open_input_file(char *filename);
int		open_output_file(char *filename, int append_mode);

int		test_input_file(char *filename);

void	check_fd_valid(int fd);
void	print_fd_content(int fd);

#endif
