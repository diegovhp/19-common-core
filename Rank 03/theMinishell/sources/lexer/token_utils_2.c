/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:16 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/25 05:24:01 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	connect_replacement_chain(t_token *target_node,
						t_token *iterator, t_token *replacement)
{
	t_token	*chain_end;

	while (iterator != target_node)
		iterator = iterator->next;
	replacement->prev = iterator->prev;
	iterator->prev->next = replacement;
	chain_end = replacement;
	while (chain_end->next != NULL)
		chain_end = chain_end->next;
	iterator->next->prev = chain_end;
	chain_end->next = iterator->next;
}

static bool	handle_head_replacement(t_token **list_head,
						t_token *target_node, t_token *replacement)
{
	if (*list_head != target_node)
		return (false);
	*list_head = replacement;
	replacement->next = target_node->next;
	if (target_node->next)
		target_node->next->prev = replacement;
	return (true);
}

static void	deallocate_old_node(t_token *node)
{
	cleanup_pointer(node->str);
	cleanup_pointer(node);
}

t_token	*substitute_node_with_chain(t_token **list_head,
						t_token *old_node, t_token *new_chain)
{
	t_token	*list_walker;

	if (!*list_head)
	{
		*list_head = new_chain;
		deallocate_old_node(old_node);
		return (new_chain);
	}
	if (handle_head_replacement(list_head, old_node, new_chain))
	{
		deallocate_old_node(old_node);
		return (new_chain);
	}
	list_walker = *list_head;
	connect_replacement_chain(old_node, list_walker, new_chain);
	deallocate_old_node(old_node);
	return (new_chain);
}
