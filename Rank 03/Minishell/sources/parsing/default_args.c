/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:05 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/25 06:04:41 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Copie tous les anciens arg de last_cmd->args -> nouveau tableau new_tab
// add les nouveaux mots WORD/VAR à la suite depuis les tokens à partir de 
//tk_node
static char	**transfer_existing_to_expanded(
	int len, char **new_tab, t_command *last_cmd, t_token **tk_node)
{
	int		position;
	t_token	*current;

	position = 0;
	current = *tk_node;
	while (position < len)
	{
		new_tab[position] = last_cmd->args[position];
		position++;
	}
	while (current->type == WORD || current->type == VAR)
	{
		new_tab[position] = ft_strdup(current->str);
		position++;
		current = current->next;
	}
	new_tab[position] = NULL;
	return (new_tab);
}

// compte le nbr de token WORD/VAR consecutifs a partir du token temp
int	calculate_word_tokens(t_token *temp)
{
	int	counter;

	counter = 0;
	while (temp && (temp->type == WORD || temp->type == VAR))
	{
		counter++;
		temp = temp->next;
	}
	return (counter);
}

// arguments -> last cmd selon le nom. si echo = init echo args
// sinon init standard args ou extend standard arg
int	populate_command_arguments(t_token **token_node, t_command *last_cmd)
{
	if (!ft_strcmp(last_cmd->command, "echo"))
	{
		if (!(last_cmd->args))
			return (initialize_echo_arguments(token_node, last_cmd));
		else
			return (extend_echo_arguments(token_node, last_cmd));
	}
	else
	{
		if (last_cmd && !(last_cmd->args))
			return (initialize_standard_arguments(token_node, last_cmd));
		else
			return (extend_standard_arguments(token_node, last_cmd));
	}
	return (SUCCESS);
}

// extend dynamiquement les arg de la cmd actuelle
// en ajoutant tokens WORD/VAR suivant les args deja presents
int	extend_standard_arguments(t_token **token_node, t_command *last_cmd)
{
	int		token_count;
	int		current_len;
	char	**new_array;
	t_token	*current;

	current = *token_node;
	token_count = 0;
	while (current->type == WORD || current->type == VAR)
	{
		token_count++;
		current = current->next;
	}
	current_len = 0;
	while (last_cmd->args[current_len])
		current_len++;
	new_array = malloc(sizeof(char *) * (token_count + current_len + 1));
	if (!new_array)
		return (FAILURE);
	new_array = transfer_existing_to_expanded(current_len,
			new_array, last_cmd, token_node);
	free(last_cmd->args);
	last_cmd->args = new_array;
	*token_node = current;
	return (SUCCESS);
}

// init args d'1 cmd a partir du nom et des tokens suivants
// allocate char tab
// stock cmd in args[0] et args dans args[1] etc
int	initialize_standard_arguments(t_token **token_node, t_command *last_cmd)
{
	int		position;
	int		arg_count;
	t_token	*current;

	current = *token_node;
	arg_count = calculate_word_tokens(current);
	last_cmd->args = malloc(sizeof(char *) * (arg_count + 2));
	if (!last_cmd->args)
		return (FAILURE);
	current = *token_node;
	position = 0;
	last_cmd->args[position] = ft_strdup(last_cmd->command);
	position++;
	while (current->type == WORD || current->type == VAR)
	{
		last_cmd->args[position] = ft_strdup(current->str);
		position++;
		current = current->next;
	}
	last_cmd->args[position] = NULL;
	*token_node = current;
	return (SUCCESS);
}
