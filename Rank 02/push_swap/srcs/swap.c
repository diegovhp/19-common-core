/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:14:46 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/16 17:19:53 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	swap(t_stack_node **stack)
{
	if (!*stack || !(*stack)->next)
		return ;
	*stack = (*stack)->next;
	(*stack)->prev->prev = *stack;
	(*stack)->prev->next = (*stack)->next;
	if ((*stack)->next)
		(*stack)->next->prev = (*stack)->prev;
	(*stack)->next = (*stack)->prev;
	(*stack)->prev = NULL;
}

void	sa(t_stack_node **a, bool show)
{
	swap(a);
	if (show)
		ft_printf("sa\n");
}

void	sb(t_stack_node **b, bool show)
{
	swap(b);
	if (show)
		ft_printf("sb\n");
}

void	ss(t_stack_node **a, t_stack_node **b, bool show)
{
	swap(a);
	swap(b);
	if (show)
		ft_printf("ss\n");
}
