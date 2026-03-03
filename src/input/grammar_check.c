/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:26:25 by dsagong           #+#    #+#             */
/*   Updated: 2026/03/03 15:44:42 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "utils.h"
#include "libft.h"
#include "state.h"

static int	check_quote_error(const char *input)
{
	t_quote_state	state;
	size_t			i;

	state = STATE_GENERAL;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			state = state_machine(input[i], state);
		i++;
	}
	if (state != STATE_GENERAL)
	{
		print_quote_error(state);
		return (1);
	}
	return (0);
}

static t_grammar_status	check_pipe(t_token *token)
{
	if (token->next->type == T_END)
	{
		token->type = T_ERROR;
		return (GRAMMAR_EOF_ERROR);
	}
	if (token->next->type == T_PIPE)
	{
		token->next->type = T_ERROR;
		return (GRAMMAR_TOKEN_ERROR);
	}
	return (GRAMMAR_OK);
}

static t_grammar_status	check_redir(t_token *token)
{
	if (token->next->type != T_WORD)
	{
		token->next->type = T_ERROR;
		return (GRAMMAR_TOKEN_ERROR);
	}
	return (GRAMMAR_OK);
}

static t_grammar_status	check_token_error(t_token *token_lst)
{
	t_grammar_status	status;

	while (token_lst && token_lst->type != T_END)
	{
		status = GRAMMAR_OK;
		if (token_lst->type == T_PIPE)
			status = check_pipe(token_lst);
		else if (is_redir_type(token_lst->type))
			status = check_redir(token_lst);
		if (status != GRAMMAR_OK)
			return (status);
		token_lst = token_lst->next;
	}
	return (GRAMMAR_OK);
}

/**
 * [Fail-Fast Grammar Validation]
 * 실행 단계로 넘어가기 전, 복합적인 문법 오류를 사전에 차단
 * - Unclosed Quotes: 종결되지 않은 따옴표 체크
 * - Operator Misuse: 연속된 파이프(||)나 리다이렉션 뒤에 인자가 없는 경우 등
 * 이를 통해 불필요한 프로세스 생성을 막고 쉘의 안정성을 확보
 */
t_grammar_status	grammar_check(t_prompt *prompt)
{
	t_grammar_status	status;

	if (check_quote_error(prompt->input))
		return (GRAMMAR_EOF_ERROR);
	status = check_token_error(prompt->token_lst);
	return (status);
}
