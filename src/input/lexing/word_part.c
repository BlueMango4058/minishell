/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_part.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:03:51 by dsagong           #+#    #+#             */
/*   Updated: 2026/03/03 15:42:16 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "utils.h"

static char	*skip_quotes(char *s)
{
	char	qc;

	qc = *s;
	s++;
	while (*s && *s != qc)
		s++;
	if (*s == qc)
		return (++s);
	return (s);
}

static int	get_word_length(char *input)
{
	char	*start;

	start = input;
	while (*input && !is_space(*input) && !is_operator(*input))
	{
		if (*input == '\'' || *input == '"')
			input = skip_quotes(input);
		else
			input++;
	}
	return (input - start);
}

/**
 * [Word Token Handling with Quote Protection]
 * 일반 텍스트 토큰을 추출합니다. 
 * 핵심 설계: 따옴표(' 또는 ")를 만나면 대응하는 닫는 따옴표가 나올 때까지 
 * 내부의 공백이나 연산자 문자를 일반 문자로 취급하여 하나의 단어로 보존
 * - skip_quotes: 따옴표 내부의 데이터 무결성을 보장하며 인덱스를 건너뜀
 * - get_word_length: 문맥을 고려하여 실제 단어의 길이를 정밀하게 계산
 */
int	handle_word(t_token **token_lst, char *input)
{
	int				len;
	char			*value;

	len = get_word_length(input);
	if (len == 0)
		return (-1);
	value = ft_my_strndup(input, len);
	if (!value)
		return (-1);
	if (add_new_token(token_lst, value, T_WORD))
		return (len);
	return (-1);
}
