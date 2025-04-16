/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:13:38 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/16 17:19:38 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	rotate(t_stack_node **stack)
{
	t_stack_node	*last_node;

	if (!*stack || !(*stack)->next)
		return ;
	last_node = ft_last_node(*stack);
	last_node->next = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	last_node->next->prev = last_node;
	last_node->next->next = NULL;
}

void	ra(t_stack_node **a, bool show)
{
	rotate(a);
	if (show)
		ft_printf("ra\n");
}

void	rb(t_stack_node **b, bool show)
{
	rotate(b);
	if (show)
		ft_printf("rb\n");
}

void	rr(t_stack_node **a, t_stack_node **b, bool show)
{
	rotate(a);
	rotate(b);
	if (show)
		ft_printf("rr\n");
}
