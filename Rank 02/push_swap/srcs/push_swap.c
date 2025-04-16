/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:13:01 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/16 18:41:09 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
void	print_stack(t_stack_node *stack)
{
	t_stack_node	*current;

	if (!stack)
	{
		printf("Stack is empty\n");
		return ;
	}
	current = stack;
	while (current)
	{
		printf("%d\n", current->nbr);
		current = current->next;
	}
}
	printf("Sorted stack A:\n");
	print_stack(a);
*/

int	check(char *check)
{
	int	i;

	i = 0;
	while (check[i])
	{
		if (check[i] == ' ')
			return (0);
		i++;
	}
	return (1);
}

// int	main(int ac, char **argv)
// {
// 	t_stack_node	*a;
// 	t_stack_node	*b;
// 	char			**av;
// 	int				yo;
// 	int				i;

// 	a = NULL;
// 	b = NULL;
// 	if (ac == 1 || (ac == 2 && !argv[1][0]) || (ac == 2 && check(argv[1])))
// 		return (1);
// 	else if (ac == 2)
// 	{
// 		av = split(argv[1], ' ');
// 		if (!av)
// 			return (0);
// 		yo = 1;
// 	}
// 	else
// 	{
// 		yo = 0;
// 		av = argv;
// 	}
// 	define_stack_a(&a, av, yo);
// 	if (!is_stack_sorted(a))
// 	{
// 		if (stack_size(a) == 2)
// 			sa(&a, true);
// 		else if (stack_size(a) == 3)
// 			sort_three(&a);
// 		else
// 			sort_stack(&a, &b);
// 	}
// 	ft_free_stack(&a);
// 	i = 0;
// 	if (yo)
// 	{
// 		while (av[i])
// 		{
// 			free(av[i]);
// 			i++;
// 		}
// 		if (av || *av)
// 			free(av);
// 	}
// 	return (0);
// }
static char	**parse_args(int ac, char **argv, int *yo)
{
	char	**av;

	if (ac == 2)
	{
		av = split(argv[1], ' ');
		if (!av)
			return (NULL);
		*yo = 1;
	}
	else
	{
		*yo = 0;
		av = argv;
	}
	return (av);
}

static void	free_split_args(char **av, int yo)
{
	int	i;

	if (yo)
	{
		i = 0;
		while (av[i])
			free(av[i++]);
		if (av && *av)
			free(av);
	}
}

int	main(int ac, char **argv)
{
	t_stack_node	*a;
	t_stack_node	*b;
	char			**av;
	int				yo;

	a = NULL;
	b = NULL;
	if (ac == 1 || (ac == 2 && !argv[1][0]) || (ac == 2 && check(argv[1])))
		return (1);
	av = parse_args(ac, argv, &yo);
	if (ac == 2 && !av)
		return (0);
	define_stack_a(&a, av, yo);
	if (!is_stack_sorted(a))
	{
		if (stack_size(a) == 2)
			sa(&a, true);
		else if (stack_size(a) == 3)
			sort_three(&a);
		else
			sort_stack(&a, &b);
	}
	ft_free_stack(&a);
	free_split_args(av, yo);
	return (0);
}
