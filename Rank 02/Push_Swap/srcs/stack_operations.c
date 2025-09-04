/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 04:52:07 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/07/30 04:58:17 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_node	*get_last_node(t_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

int	get_stack_len(t_node *stack)
{
	int	count;

	if (!stack)
		return (0);
	count = 0;
	while (stack)
	{
		stack = stack->next;
		count++;
	}
	return (count);
}

bool	is_sorted(t_node *stack)
{
	if (!stack)
		return (true);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (false);
		stack = stack->next;
	}
	return (true);
}

t_node	*find_min_node(t_node *stack)
{
	long	min_val;
	t_node	*min_node;

	if (!stack)
		return (NULL);
	min_val = LONG_MAX;
	while (stack)
	{
		if (stack->value < min_val)
		{
			min_val = stack->value;
			min_node = stack;
		}
		stack = stack->next;
	}
	return (min_node);
}

t_node	*find_max_node(t_node *stack)
{
	long	max_val;
	t_node	*max_node;

	if (!stack)
		return (NULL);
	max_val = LONG_MIN;
	while (stack)
	{
		if (stack->value > max_val)
		{
			max_val = stack->value;
			max_node = stack;
		}
		stack = stack->next;
	}
	return (max_node);
}
