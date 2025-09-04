/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:04:46 by dvan-hem          #+#    #+#             */
/*   Updated: 2024/10/28 15:00:15 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	letter;

	letter = 0;
	while (letter < n && s1[letter] && s2[letter] && s1[letter] == s2[letter])
		letter++;
	if (letter == n)
		return (0);
	return ((unsigned char)s1[letter] - (unsigned char)s2[letter]);
}
