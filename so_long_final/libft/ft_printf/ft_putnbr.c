/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:40:22 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/01/07 15:43:08 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	if (n < 0)
	{
		i += ft_putchar('-');
		n = -n;
	}
	if (n > 9)
		i += ft_putnbr(n / 10);
	i += ft_putchar((n % 10) + '0');
	return (i);
}

int	ft_putunbr(unsigned int n)
{
	int	i;

	i = 0;
	if (n > 9)
		i += ft_putunbr(n / 10);
	i += ft_putchar((n % 10) + '0');
	return (i);
}
