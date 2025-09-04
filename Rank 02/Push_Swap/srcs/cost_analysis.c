/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost_analysis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 04:53:35 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/07/30 04:57:58 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	analyze_stack_positions(t_node *stack)
{
	int	index;
	int	median_point;

	index = 0;
	if (!stack)
		return ;
	median_point = get_stack_len(stack) / 2;
	while (stack)
	{
		stack->position = index;
		if (index <= median_point)
			stack->above_median = true;
		else
			stack->above_median = false;
		stack = stack->next;
		++index;
	}
}

void	set_targets_a_to_b(t_node *a, t_node *b)
{
	t_node	*current_b;
	t_node	*best_target;
	long	closest_smaller;

	while (a)
	{
		closest_smaller = LONG_MIN;
		current_b = b;
		while (current_b)
		{
			if (current_b->value < a->value
				&& current_b->value > closest_smaller)
			{
				closest_smaller = current_b->value;
				best_target = current_b;
			}
			current_b = current_b->next;
		}
		if (closest_smaller == LONG_MIN)
			a->target = find_max_node(b);
		else
			a->target = best_target;
		a = a->next;
	}
}

void	set_targets_b_to_a(t_node *a, t_node *b)
{
	t_node	*current_a;
	t_node	*best_target;
	long	closest_bigger;

	while (b)
	{
		closest_bigger = LONG_MAX;
		current_a = a;
		while (current_a)
		{
			if (current_a->value > b->value
				&& current_a->value < closest_bigger)
			{
				closest_bigger = current_a->value;
				best_target = current_a;
			}
			current_a = current_a->next;
		}
		if (closest_bigger == LONG_MAX)
			b->target = find_min_node(a);
		else
			b->target = best_target;
		b = b->next;
	}
}

void	calculate_move_costs(t_node *a, t_node *b)
{
	int	len_a;
	int	len_b;

	len_a = get_stack_len(a);
	len_b = get_stack_len(b);
	while (a)
	{
		a->cost = a->position;
		if (!(a->above_median))
			a->cost = len_a - (a->position);
		if (a->target->above_median)
			a->cost += a->target->position;
		else
			a->cost += len_b - (a->target->position);
		a = a->next;
	}
}

void	mark_optimal_node(t_node *stack)
{
	long	lowest_cost;
	t_node	*optimal_node;

	if (!stack)
		return ;
	lowest_cost = LONG_MAX;
	while (stack)
	{
		if (stack->cost < lowest_cost)
		{
			lowest_cost = stack->cost;
			optimal_node = stack;
		}
		stack = stack->next;
	}
	optimal_node->is_optimal = true;
}
