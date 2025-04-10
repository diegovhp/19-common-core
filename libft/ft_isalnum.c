/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:27:34 by dvan-hem          #+#    #+#             */
/*   Updated: 2024/10/28 14:49:54 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/*#include <stdio.h>

int	main(void)
{
	char test = '1';
	char test2 = 'A';
	char test3 = 'e';
	char test4 = '$';

	printf("%d\n", ft_isalnum(test));
	printf("%d\n", ft_isalnum(test2));
	printf("%d\n", ft_isalnum(test3));
	printf("%d\n", ft_isalnum(test4));
	return (0);
}*/
