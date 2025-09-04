/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_algorithm2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:25:11 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/08/07 18:30:10 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	final_rotation(t_node **a)
{
	while ((*a)->value != find_min_node(*a)->value)
	{
		if (find_min_node(*a)->above_median)
			ra(a, true);
		else
			rra(a, true);
	}
}

void	sort_stack(t_node **a, t_node **b)
{
	push_all_but_three(a, b);
	sort_three_nodes(a);
	push_back_to_a(a, b);
	analyze_stack_positions(*a);
	final_rotation(a);
}
