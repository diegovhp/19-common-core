/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:37:39 by dvan-hem          #+#    #+#             */
/*   Updated: 2024/11/06 19:42:22 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	totalsz;
	void	*ptr;

	totalsz = count * size;
	if (count != 0 && totalsz / count != size)
		return (NULL);
	ptr = (void *)malloc(totalsz);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, totalsz);
	return (ptr);
}
/*possibilité  de protéger en mettant si le total est superieur a intmax
pour le count * size qui peut overflow*/