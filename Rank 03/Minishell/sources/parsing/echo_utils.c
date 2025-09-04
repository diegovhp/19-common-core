/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:10 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/25 05:52:36 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// concat multpiple VAR ex $USER$HOME
static char	*merge_joined_variable_tokens(t_token **token_node)
{
	t_token	*iterator;
	char	*combined_string;

	iterator = *token_node;
	combined_string = ft_strdup(iterator->str);
	while (iterator->type == VAR && iterator->next->type == VAR
		&& iterator->next->join == true)
	{
		combined_string = ft_strjoin(combined_string, iterator->next->str);
		iterator = iterator->next;
	}
	*token_node = iterator;
	return (combined_string);
}

// delete empty VAR tokens
void	filter_empty_variable_args(t_token **tokens)
{
	t_token	*walker;

	walker = *tokens;
	while (walker->type == WORD || walker->type == VAR)
	{
		if (walker->type == VAR && walker->str[0] == '\0'
			&& walker->var_exists == false)
		{
			walker = walker->next;
			if (walker == (*tokens)->next)
				(*tokens) = (*tokens)->next;
			delete_token_node(walker->prev, cleanup_pointer);
		}
		else
			walker = walker->next;
	}
}

// compte cb d'args seront generes
int	calculate_expanded_args(t_token *scanner)
{
	int	arg_count;

	arg_count = 0;
	while (scanner && (scanner->type == WORD || scanner->type == VAR))
	{
		if (scanner->type == VAR && scanner->join == true)
		{
			while (scanner->type == VAR && scanner->join == true)
				scanner = scanner->next;
			arg_count++;
		}
		else
		{
			arg_count++;
			scanner = scanner->next;
		}
	}
	return (arg_count);
}

char	*concatenate_variable_tokens(t_token **token_node)
{
	return (merge_joined_variable_tokens(token_node));
}

// recreate tableau args avec new tokens
char	**duplicate_args_with_expansion(int len, char **new_tab,
	t_command *last_cmd, t_token *processor)
{
	int	position;

	position = 0;
	while (position < len)
	{
		new_tab[position] = last_cmd->args[position];
		position++;
	}
	while (processor->type == WORD || processor->type == VAR)
	{
		if (processor->join == true)
			new_tab[position] = merge_joined_variable_tokens(&processor);
		else
			new_tab[position] = ft_strdup(processor->str);
		position++;
		processor = processor->next;
	}
	new_tab[position] = NULL;
	return (new_tab);
}
