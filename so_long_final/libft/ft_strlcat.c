/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:33:19 by dvan-hem          #+#    #+#             */
/*   Updated: 2024/11/05 16:34:18 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	a;
	unsigned int	b;
	size_t			dest_l;
	size_t			src_l;

	a = 0;
	b = 0;
	dest_l = 0;
	src_l = 0;
	while (dest[dest_l])
		dest_l++;
	while (src[src_l])
		src_l++;
	if (size <= dest_l)
		return (size + src_l);
	a = dest_l;
	while (src[b] && a < size - 1)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	dest[a] = '\0';
	return (dest_l + src_l);
}
