/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:37:35 by dvan-hem          #+#    #+#             */
/*   Updated: 2024/11/05 16:24:32 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*src;
	unsigned char		target;
	size_t				i;

	src = (const unsigned char *)s;
	target = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (src[i] == target)
			return ((void *)(src + i));
		i++;
	}
	return (NULL);
}
