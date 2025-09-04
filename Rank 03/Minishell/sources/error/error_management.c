/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:20:45 by tstevens          #+#    #+#             */
/*   Updated: 2025/08/07 16:21:51 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Concatène deux chaînes, libère
la première chaîne initiale et retourne la nouvelle.*/
char	*concatenate_strings(char *str, char *add)
{
	char	*original_str;
	char	*new_string;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	original_str = str;
	new_string = ft_strjoin(original_str, add);
	cleanup_pointer(original_str);
	return (new_string);
}

/*Vérifie si la commande est "export" ou "unset" pour
décider d'encadrer les détails d'erreur par des quotes.*/
static bool	requires_quote_formatting(char *command)
{
	bool	is_export;
	bool	is_unset;
	bool	needs_quotes;

	is_export = (ft_strncmp(command, "export", 7) == 0);
	is_unset = (ft_strncmp(command, "unset", 6) == 0);
	needs_quotes = (is_export || is_unset);
	return (needs_quotes);
}

/*Construit et affiche un message d'erreur formaté
pour une commande, en option avec détails et quotes,
puis retourne un code d'erreur.*/
int	print_command_error(char *command, char *detail,
				char *error_message, int error_nb)
{
	char	*message_buffer;
	bool	use_quotes;
	int		return_code;

	use_quotes = requires_quote_formatting(command);
	message_buffer = ft_strdup("minishell: ");
	return_code = error_nb;
	if (command != NULL)
	{
		message_buffer = concatenate_strings(message_buffer, command);
		message_buffer = concatenate_strings(message_buffer, ": ");
	}
	if (detail != NULL)
	{
		if (use_quotes)
			message_buffer = concatenate_strings(message_buffer, "`");
		message_buffer = concatenate_strings(message_buffer, detail);
		if (use_quotes)
			message_buffer = concatenate_strings(message_buffer, "'");
		message_buffer = concatenate_strings(message_buffer, ": ");
	}
	message_buffer = concatenate_strings(message_buffer, error_message);
	ft_putendl_fd(message_buffer, STDERR_FILENO);
	cleanup_pointer(message_buffer);
	return (return_code);
}

/*Affiche un message d'erreur de syntaxe
avec ou sans guillemets autour du détail.*/
void	print_syntax_error(char *errmsg, char *detail, int quotes)
{
	char	*error_buffer;
	bool	should_quote;

	error_buffer = ft_strdup("minishell: ");
	should_quote = (quotes != 0);
	error_buffer = concatenate_strings(error_buffer, errmsg);
	if (should_quote)
		error_buffer = concatenate_strings(error_buffer, " `");
	else
		error_buffer = concatenate_strings(error_buffer, ": ");
	error_buffer = concatenate_strings(error_buffer, detail);
	if (should_quote)
		error_buffer = concatenate_strings(error_buffer, "'");
	ft_putendl_fd(error_buffer, STDERR_FILENO);
	cleanup_pointer(error_buffer);
}

/*Affiche les instructions d'utilisation
du minishell et retourne la valeur passée en argument.*/
bool	display_usage(bool return_value)
{
	bool	result;
	int		stderr_fd;

	result = return_value;
	stderr_fd = 2;
	ft_putendl_fd("Usage: ./minishell", stderr_fd);
	ft_putendl_fd("Usage: ./minishell -c \"input line\"", stderr_fd);
	return (result);
}
