/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:57:00 by dsagong           #+#    #+#             */
/*   Updated: 2025/09/17 13:57:01 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_H
# define OUTPUT_H

# include "types.h"
# include "utils.h"
# include "parser.h"
# include "executor.h"

int	output_process(t_shell *shell, t_prompt *prompt);

#endif
