/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:14:40 by dvan-hem          #+#    #+#             */
/*   Updated: 2024/10/28 14:49:57 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
/*#include <stdio.h>

int	main(void)
{
	char test = '1';
	char test2 = 'k';

	printf("%d\n", ft_isdigit(test));
	printf("%d\n", ft_isdigit(test2));
	return (0);
}*/
