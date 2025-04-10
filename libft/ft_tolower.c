/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:56:30 by dvan-hem          #+#    #+#             */
/*   Updated: 2024/10/28 14:59:49 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c += 32;
		return (c);
	}
	else
		return (c);
}
/*#include <stdio.h>

int	main(void)
{
	int i = 'a';
	int j = 'A';
	int k = '3';

	printf("%c\n", ft_tolower(i));
	printf("%c\n", ft_tolower(j));
	printf("%c\n", ft_tolower(k));
	return (0);
}*/
