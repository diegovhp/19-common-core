/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 04:54:04 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/07/30 04:58:13 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	count_tokens(char *str, char sep)
{
	int		count;
	bool	inside_token;

	count = 0;
	while (*str)
	{
		inside_token = false;
		while (*str == sep)
			++str;
		while (*str != sep && *str)
		{
			if (!inside_token)
			{
				++count;
				inside_token = true;
			}
			++str;
		}
	}
	return (count);
}

static char	*extract_token(char *str, char sep)
{
	static int	position = 0;
	char		*token;
	int			length;
	int			i;

	length = 0;
	i = 0;
	while (str[position] == sep)
		++position;
	while ((str[position + length] != sep) && str[position + length])
		++length;
	token = malloc((size_t)length * sizeof(char) + 1);
	if (!token)
		return (NULL);
	while ((str[position] != sep) && str[position])
		token[i++] = str[position++];
	token[i] = '\0';
	return (token);
}

char	**split_arguments(char *str, char sep)
{
	int		token_count;
	char	**result;
	int		i;

	i = 0;
	token_count = count_tokens(str, sep);
	if (!token_count)
		exit(1);
	result = malloc(sizeof(char *) * (size_t)(token_count + 2));
	if (!result)
		return (NULL);
	while (token_count-- >= 0)
	{
		if (i == 0)
		{
			result[i] = malloc(sizeof(char));
			if (!result[i])
				return (NULL);
			result[i++][0] = '\0';
			continue ;
		}
		result[i++] = extract_token(str, sep);
	}
	result[i] = NULL;
	return (result);
}
