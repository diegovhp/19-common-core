/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:12:39 by dvan-hem          #+#    #+#             */
/*   Updated: 2024/11/06 19:19:06 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_space(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (i < (size_t)ft_strlen(set))
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		max;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	max = ft_strlen(s1);
	while (is_space(s1[i], set))
		i++;
	while (max > i && is_space(s1[max - 1], set))
		max--;
	res = ft_calloc(max - i + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1 + i, max - i + 1);
	return (res);
}
