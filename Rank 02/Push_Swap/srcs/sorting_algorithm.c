/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 04:53:11 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/07/30 04:58:10 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static t_node	*find_optimal_node(t_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack)
	{
		if (stack->is_optimal)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

static void	execute_optimal_move(t_node **a, t_node **b)
{
	t_node	*optimal_node;

	optimal_node = find_optimal_node(*a);
	if (optimal_node->above_median && optimal_node->target->above_median)
		execute_combined_rotations(a, b, optimal_node);
	else if (!(optimal_node->above_median)
		&& !(optimal_node->target->above_median))
		execute_combined_reverse(a, b, optimal_node);
	move_node_to_top(a, optimal_node, 'a');
	move_node_to_top(b, optimal_node->target, 'b');
	pb(b, a, true);
}

void	push_all_but_three(t_node **a, t_node **b)
{
	int	stack_len;

	stack_len = get_stack_len(*a);
	if (stack_len-- > 3 && !is_sorted(*a))
		pb(b, a, true);
	if (stack_len-- > 3 && !is_sorted(*a))
		pb(b, a, true);
	while (stack_len-- > 3 && !is_sorted(*a))
	{
		analyze_stack_positions(*a);
		analyze_stack_positions(*b);
		set_targets_a_to_b(*a, *b);
		calculate_move_costs(*a, *b);
		mark_optimal_node(*a);
		execute_optimal_move(a, b);
	}
}

void	push_back_to_a(t_node **a, t_node **b)
{
	while (*b)
	{
		analyze_stack_positions(*a);
		analyze_stack_positions(*b);
		set_targets_b_to_a(*a, *b);
		move_node_to_top(a, (*b)->target, 'a');
		pa(a, b, true);
	}
}

void	sort_three_nodes(t_node **a)
{
	t_node	*max_node;

	max_node = find_max_node(*a);
	if (max_node == *a)
		ra(a, true);
	else if ((*a)->next == max_node)
		rra(a, true);
	if ((*a)->value > (*a)->next->value)
		sa(a, true);
}
