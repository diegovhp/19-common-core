/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_moves.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 04:52:52 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/07/30 04:57:47 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rrr(t_node **a, t_node **b, bool print)
{
	rra(a, false);
	rrb(b, false);
	if (print)
		ft_printf("rrr\n");
}

void	move_node_to_top(t_node **stack, t_node *node, char stack_name)
{
	while (*stack != node)
	{
		if (stack_name == 'a')
		{
			if (node->above_median)
				ra(stack, true);
			else
				rra(stack, true);
		}
		else if (stack_name == 'b')
		{
			if (node->above_median)
				rb(stack, true);
			else
				rrb(stack, true);
		}
	}
}

void	execute_combined_rotations(t_node **a, t_node **b, t_node *optimal)
{
	while (*b != optimal->target && *a != optimal)
		rr(a, b, true);
	analyze_stack_positions(*a);
	analyze_stack_positions(*b);
}

void	execute_combined_reverse(t_node **a, t_node **b, t_node *optimal)
{
	while (*b != optimal->target && *a != optimal)
		rrr(a, b, true);
	analyze_stack_positions(*a);
	analyze_stack_positions(*b);
}
