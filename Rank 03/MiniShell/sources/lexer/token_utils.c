/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:21 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/22 19:49:17 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*make_token(char *content, char *backup_content,
									int token_type, int token_status)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token) * 1);
	if (!(new_token))
		return (NULL);
	new_token->str = content;
	new_token->str_save = backup_content;
	new_token->var_exists = false;
	new_token->type = token_type;
	new_token->status = token_status;
	new_token->join = false;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	add_token_to_end(t_token **head_ref, t_token *node_to_add)
{
	t_token	*current_node;

	current_node = *head_ref;
	if (current_node == NULL)
	{
		*head_ref = node_to_add;
		return ;
	}
	if (head_ref && *head_ref && node_to_add)
	{
		while (current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = node_to_add;
		node_to_add->prev = current_node;
	}
}

void	delete_token_node(t_token *node_to_delete,
						void (*deletion_func)(void *))
{
	if (deletion_func && node_to_delete && node_to_delete->str)
	{
		(*deletion_func)(node_to_delete->str);
		node_to_delete->str = NULL;
	}
	if (deletion_func && node_to_delete && node_to_delete->str_save)
	{
		(*deletion_func)(node_to_delete->str_save);
		node_to_delete->str_save = NULL;
	}
	if (node_to_delete->prev)
		node_to_delete->prev->next = node_to_delete->next;
	if (node_to_delete->next)
		node_to_delete->next->prev = node_to_delete->prev;
	cleanup_pointer(node_to_delete);
}

void	free_entire_token_list(t_token **head_ref,
						void (*deletion_func)(void *))
{
	t_token	*following_node;

	following_node = NULL;
	while (*head_ref != NULL)
	{
		following_node = (*head_ref)->next;
		delete_token_node(*head_ref, deletion_func);
		*head_ref = following_node;
	}
}
