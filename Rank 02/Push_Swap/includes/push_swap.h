/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 04:51:14 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/07/30 04:51:26 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_node
{
	int				value;
	int				position;
	int				cost;
	bool			above_median;
	bool			is_optimal;
	struct s_node	*target;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

// main.c
int		main(int argc, char **argv);

// parsing.c  
void	parse_and_init(t_node **stack_a, char **args, bool split_needed);
bool	validate_input(char *str);
long	convert_to_long(const char *str);
int		add_node_to_stack(t_node **stack, int value);

// stack_operations.c
int		get_stack_len(t_node *stack);
t_node	*get_last_node(t_node *stack);
bool	is_sorted(t_node *stack);
t_node	*find_min_node(t_node *stack);
t_node	*find_max_node(t_node *stack);

// basic_moves.c
void	sa(t_node **a, bool print);
void	sb(t_node **b, bool print);
void	ss(t_node **a, t_node **b, bool print);
void	pa(t_node **a, t_node **b, bool print);
void	pb(t_node **b, t_node **a, bool print);

// rotation_moves.c
void	ra(t_node **a, bool print);
void	rb(t_node **b, bool print);
void	rr(t_node **a, t_node **b, bool print);
void	rra(t_node **a, bool print);
void	rrb(t_node **b, bool print);

// advanced_moves.c
void	rrr(t_node **a, t_node **b, bool print);
void	move_node_to_top(t_node **stack, t_node *node, char stack_name);
void	execute_combined_rotations(t_node **a, t_node **b, t_node *optimal);
void	execute_combined_reverse(t_node **a, t_node **b, t_node *optimal);

// sorting_algorithm.c
void	sort_stack(t_node **a, t_node **b);
void	sort_three_nodes(t_node **a);
void	push_all_but_three(t_node **a, t_node **b);
void	push_back_to_a(t_node **a, t_node **b);
void	final_rotation(t_node **a);

// cost_analysis.c
void	analyze_stack_positions(t_node *stack);
void	set_targets_a_to_b(t_node *a, t_node *b);
void	set_targets_b_to_a(t_node *a, t_node *b);
void	calculate_move_costs(t_node *a, t_node *b);
void	mark_optimal_node(t_node *stack);

// memory_management.c
void	free_stack(t_node **stack);
void	handle_error(t_node **a, char **args, bool need_free_args);
bool	has_duplicates(t_node *stack, int value);
char	**split_arguments(char *str, char delimiter);
void	free_split_result(char **split);

// printing.c (pour debug si nécessaire)
void	ft_printf(const char *format, ...);

#endif
