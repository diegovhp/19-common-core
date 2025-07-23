/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:16 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 11:19:23 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	link_new_segment_boundaries(t_token *old_node,
						t_token *walker, t_token *new_chain)
{
	while (walker != old_node)
		walker = walker->next;
	new_chain->prev = walker->prev;
	walker->prev->next = new_chain;
	while (new_chain->next)
		new_chain = new_chain->next;
	walker->next->prev = new_chain;
	new_chain->next = walker->next;
}

t_token	*substitute_node_with_chain(t_token **list_head,
						t_token *old_node, t_token *new_chain)
{
	t_token	*traverser;

	traverser = *list_head;
	if (traverser == NULL)
		*list_head = new_chain;
	else if (traverser == old_node)
	{
		*list_head = new_chain;
		new_chain->next = traverser->next;
		if (traverser->next != NULL)
			traverser->next->prev = new_chain;
	}
	else
		link_new_segment_boundaries(old_node, traverser, new_chain);
	cleanup_pointer(old_node->str);
	cleanup_pointer(old_node);
	return (new_chain);
}
