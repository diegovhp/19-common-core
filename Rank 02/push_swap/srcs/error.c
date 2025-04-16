/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:12:25 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/16 17:18:57 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	syntax_error(char *c)
{
	if (!(*c == '+' || *c == '-' || (*c >= '0' && *c <= '9')))
		return (1);
	if ((*c == '+' || *c == '-') && !(c[1] >= '0' && c[1] <= '9'))
		return (1);
	while (*++c)
	{
		if (!(*c >= '0' && *c <= '9'))
			return (1);
	}
	return (0);
}

void	ft_free_stack(t_stack_node **stack)
{
	t_stack_node	*tmp;
	t_stack_node	*current;

	if (!stack)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current->next;
		current->nbr = 0;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}

void	ft_free(t_stack_node **a, char **av, int yo)
{
	int	i;

	i = 0;
	ft_free_stack(a);
	if (yo)
	{
		while (av[i])
		{
			free(av[i]);
			i++;
		}
		free(av);
	}
	ft_printf("Error\n");
	exit(1);
}

int	duplicate_error(t_stack_node *a, int n)
{
	if (!a)
		return (0);
	while (a)
	{
		if (a->nbr == n)
			return (1);
		a = a->next;
	}
	return (0);
}
