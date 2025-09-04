/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:27:26 by dvan-hem          #+#    #+#             */
/*   Updated: 2024/10/28 15:06:16 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/*#include <stdio.h>

int	main(void)
{
	char test = '1';
	char test2 = 'k';

	printf("%d\n", ft_isalpha(test));
	printf("%d\n", ft_isalpha(test2));
	return (0);
}*/
