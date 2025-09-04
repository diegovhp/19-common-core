/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:20:41 by tstevens          #+#    #+#             */
/*   Updated: 2025/08/07 16:38:09 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Libère la mémoire pointée par ptr si
non NULL et met le pointeur local à NULL.*/
void	cleanup_pointer(void *ptr)
{
	void	*target_ptr;

	target_ptr = ptr;
	if (target_ptr != NULL)
	{
		free(target_ptr);
		target_ptr = NULL;
	}
}

/*Libère chaque chaîne d'un tableau
de chaînes puis libère le tableau lui-même.*/
void	cleanup_string_array(char **tab)
{
	char	**current_tab;
	int		index;

	current_tab = tab;
	index = 0;
	if (current_tab)
	{
		while (current_tab[index])
		{
			cleanup_pointer(current_tab[index]);
			current_tab[index] = NULL;
			index++;
		}
		free(current_tab);
		current_tab = NULL;
	}
}

/*Libère et ferme les ressources liées à
la structure io, incluant fichiers temporaires et chemins.*/
void	cleanup_io_structure(t_io_fds *io)
{
	t_io_fds	*io_struct;

	io_struct = io;
	if (!io_struct)
		return ;
	reset_io_redirection(io_struct);
	if (io_struct->heredoc_limit)
	{
		unlink(io_struct->infile);
		cleanup_pointer(io_struct->heredoc_limit);
	}
	if (io_struct->infile)
		cleanup_pointer(io_struct->infile);
	if (io_struct->outfile)
		cleanup_pointer(io_struct->outfile);
	cleanup_pointer(io_struct);
}

/*Ferme les descripteurs de fichiers ouverts
dans io_fds et réinitialise les redirections si demandé.*/
void	cleanup_file_descriptors(t_command *cmds, bool close_backups)
{
	t_command	*command_ptr;
	t_io_fds	*io_ptr;

	command_ptr = cmds;
	if (command_ptr->io_fds)
	{
		io_ptr = command_ptr->io_fds;
		if (io_ptr->fd_in != -1)
			close(io_ptr->fd_in);
		if (io_ptr->fd_out != -1)
			close(io_ptr->fd_out);
		if (close_backups)
			reset_io_redirection(io_ptr);
	}
	cleanup_unused_pipe_fds(command_ptr, NULL);
}

/*Libère toutes les ressources liées à la
structure shell_data, y compris l'historique readline si demandé.*/
void	cleanup_shell_data(t_data *data, bool clear_history)
{
	t_data	*shell_data;
	bool	should_clear;

	shell_data = data;
	should_clear = clear_history;
	if (shell_data && shell_data->user_input)
	{
		cleanup_pointer(shell_data->user_input);
		shell_data->user_input = NULL;
	}
	if (shell_data && shell_data->token)
		free_entire_token_list(&shell_data->token, &cleanup_pointer);
	if (shell_data && shell_data->cmd)
		destroy_command_list(&shell_data->cmd, &cleanup_pointer);
	if (should_clear == true)
	{
		if (shell_data && shell_data->working_dir)
			cleanup_pointer(shell_data->working_dir);
		if (shell_data && shell_data->old_working_dir)
			cleanup_pointer(shell_data->old_working_dir);
		if (shell_data && shell_data->env)
			cleanup_string_array(shell_data->env);
		rl_clear_history();
	}
}
