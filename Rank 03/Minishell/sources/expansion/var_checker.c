/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:58:35 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 12:58:39 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	should_expand_var(t_token *temp, int i)
{
	if (temp->str[i] == '$'
		&& check_next_separator(temp->str[i + 1]) == false
		&& check_var_in_quotes(temp->str, i) == false
		&& (temp->status == DEFAULT || temp->status == DQUOTE))
		return (true);
	else
		return (false);
}

bool	should_expand_heredoc_var(char *str, int i)
{
	if (str[i] == '$'
		&& check_next_separator(str[i + 1]) == false
		&& check_var_in_quotes(str, i) == false)
		return (true);
	else
		return (false);
}
