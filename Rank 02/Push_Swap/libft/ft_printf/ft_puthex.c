/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:45:18 by dvan-hem          #+#    #+#             */
/*   Updated: 2024/11/19 17:01:29 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned int n, int uppercase)
{
	char	*hex_base;
	int		i;

	i = 0;
	if (uppercase)
		hex_base = "0123456789ABCDEF";
	else
		hex_base = "0123456789abcdef";
	if (n >= 16)
		i = ft_puthex(n / 16, uppercase);
	i += ft_putchar(hex_base[n % 16]);
	return (i);
}
