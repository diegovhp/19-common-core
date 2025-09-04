/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:20:51 by tstevens          #+#    #+#             */
/*   Updated: 2025/08/07 16:22:19 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Nettoie les ressources allouées
(descripteurs, données du shell) puis termine
le programme avec le code de sortie donné.*/
void	terminate_shell(t_data *data, int exno)
{
	if (data)
	{
		if (data->cmd && data->cmd->io_fds)
			cleanup_file_descriptors(data->cmd, true);
		cleanup_shell_data(data, true);
	}
	exit(exno);
}
