/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 04:51:37 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/07/30 05:25:17 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static bool	has_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

static bool	should_exit_early(int argc, char **argv)
{
	if (argc == 1)
		return (true);
	if (argc == 2 && !argv[1][0])
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	if (argc == 2 && has_only_spaces(argv[1]))
		return (true);
	return (false);
}

static char	**prepare_arguments(int argc, char **argv, bool *split_needed)
{
	char	**args;

	if (argc == 2)
	{
		args = split_arguments(argv[1], ' ');
		if (!args)
			return (NULL);
		*split_needed = true;
	}
	else
	{
		args = argv;
		*split_needed = false;
	}
	return (args);
}

static void	execute_sorting(t_node **a, t_node **b)
{
	int	stack_size;

	if (is_sorted(*a))
		return ;
	stack_size = get_stack_len(*a);
	if (stack_size == 2)
		sa(a, true);
	else if (stack_size == 3)
		sort_three_nodes(a);
	else
		sort_stack(a, b);
}

int	main(int argc, char **argv)
{
	t_node	*stack_a;
	t_node	*stack_b;
	char	**args;
	bool	split_needed;

	stack_a = NULL;
	stack_b = NULL;
	if (should_exit_early(argc, argv))
		return (1);
	args = prepare_arguments(argc, argv, &split_needed);
	if (argc == 2 && !args)
		return (0);
	parse_and_init(&stack_a, args, split_needed);
	execute_sorting(&stack_a, &stack_b);
	free_stack(&stack_a);
	if (split_needed)
		free_split_result(args);
	return (0);
}
