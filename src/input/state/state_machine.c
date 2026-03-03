/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:26:18 by dsagong           #+#    #+#             */
/*   Updated: 2026/03/03 15:44:30 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

/**
 * [Context-Aware State Machine]
 * 현재 문자가 싱글/더블 따옴표 내부인지 외부인지를 추적
 * 이 상태값은 다음 단계에서 특수 문자($, |, <, >)의 해석 여부를 결정
 */
t_quote_state	state_machine(char c, t_quote_state state)
{
	if (state == STATE_GENERAL)
	{
		if (c == '\'')
			return (STATE_IN_SQUOTE);
		if (c == '\"')
			return (STATE_IN_DQUOTE);
		return (STATE_GENERAL);
	}
	else if (state == STATE_IN_SQUOTE && c == '\'')
		return (STATE_GENERAL);
	else if (state == STATE_IN_DQUOTE && c == '\"')
		return (STATE_GENERAL);
	return (state);
}
