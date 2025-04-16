/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:13:25 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/16 17:19:35 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	reverse_rotate(t_stack_node **stack)
{
	t_stack_node	*last;

	if (!*stack || !(*stack)->next)
		return ;
	last = ft_last_node(*stack);
	last->prev->next = NULL;
	last->next = *stack;
	last->prev = NULL;
	*stack = last;
	last->next->prev = last;
}

void	rra(t_stack_node **a, bool show)
{
	reverse_rotate(a);
	if (show)
		ft_printf("rra\n");
}

void	rrb(t_stack_node **b, bool show)
{
	reverse_rotate(b);
	if (show)
		ft_printf("rrb\n");
}

void	rrr(t_stack_node **a, t_stack_node **b, bool show)
{
	reverse_rotate(a);
	reverse_rotate(b);
	if (show)
		ft_printf("rrr\n");
}
