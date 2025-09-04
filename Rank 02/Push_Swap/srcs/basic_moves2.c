/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_moves2.c                                      :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:25:19 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/08/07 18:25:49 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	push_node(t_node **dest, t_node **src)
{
	t_node	*node_to_move;

	if (!*src)
		return ;
	node_to_move = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	node_to_move->prev = NULL;
	if (!*dest)
	{
		*dest = node_to_move;
		node_to_move->next = NULL;
	}
	else
	{
		node_to_move->next = *dest;
		node_to_move->next->prev = node_to_move;
		*dest = node_to_move;
	}
}

void	pa(t_node **a, t_node **b, bool print)
{
	push_node(a, b);
	if (print)
		ft_printf("pa\n");
}

void	pb(t_node **b, t_node **a, bool print)
{
	push_node(b, a);
	if (print)
		ft_printf("pb\n");
}
