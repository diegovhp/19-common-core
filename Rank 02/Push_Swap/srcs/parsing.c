/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 04:51:50 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/02 18:55:21 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

bool	validate_input(char *str)
{
	if (!(*str == '+' || *str == '-' || (*str >= '0' && *str <= '9')))
		return (false);
	if ((*str == '+' || *str == '-') && !(str[1] >= '0' && str[1] <= '9'))
		return (false);
	while (*++str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (false);
	}
	return (true);
}

long	convert_to_long(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\f' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return (result * sign);
}

int	add_node_to_stack(t_node **stack, int value)
{
	t_node	*new_node;
	t_node	*last;

	if (!stack)
		return (1);
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (1);
	new_node->value = value;
	new_node->next = NULL;
	new_node->is_optimal = false;
	if (!(*stack))
	{
		*stack = new_node;
		new_node->prev = NULL;
	}
	else
	{
		last = get_last_node(*stack);
		last->next = new_node;
		new_node->prev = last;
	}
	return (0);
}

void	parse_and_init(t_node **stack_a, char **args, bool split_needed)
{
	long	num;
	int		i;

	i = 1;
	while (args[i])
	{
		if (!validate_input(args[i]))
			handle_error(stack_a, args, split_needed);
		num = convert_to_long(args[i]);
		if (num > INT_MAX || num < INT_MIN)
			handle_error(stack_a, args, split_needed);
		if (has_duplicates(*stack_a, (int)num))
			handle_error(stack_a, args, split_needed);
		if (add_node_to_stack(stack_a, (int)num))
			handle_error(stack_a, args, split_needed);
		i++;
	}
}
