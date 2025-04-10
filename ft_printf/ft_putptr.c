/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:05:55 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/01/07 14:28:04 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(unsigned long long n)
{
	char	*hex_base;
	int		i;

	hex_base = "0123456789abcdef";
	i = 0;
	if (n >= 16)
		i += ft_putptr(n / 16);
	i += ft_putchar(hex_base[n % 16]);
	return (i);
}
