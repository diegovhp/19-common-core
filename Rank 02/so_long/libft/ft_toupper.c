/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:47:41 by dvan-hem          #+#    #+#             */
/*   Updated: 2024/10/28 14:59:30 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c -= 32;
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

	printf("%c\n", ft_toupper(i));
	printf("%c\n", ft_toupper(j));
	printf("%c\n", ft_toupper(k));
	return (0);
}*/
