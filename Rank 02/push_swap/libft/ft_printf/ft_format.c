/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:03:54 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/01/08 15:48:50 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_ptrrule(va_list args)
{
	int		i;
	void	*ptr;

	i = 0;
	ptr = va_arg(args, void *);
	if (!ptr)
		i += ft_putstr("(nil)");
	else
	{
		i += ft_putstr("0x");
		i += ft_putptr((unsigned long)ptr);
	}
	return (i);
}

int	ft_format(va_list args, char specifier)
{
	int	i;

	i = 0;
	if (specifier == 'c')
		i += ft_putchar(va_arg(args, int));
	else if (specifier == 's')
		i += ft_putstr(va_arg(args, char *));
	else if (specifier == 'p')
		i += ft_ptrrule(args);
	else if (specifier == 'd' || specifier == 'i')
		i += ft_putnbr(va_arg(args, int));
	else if (specifier == 'u')
		i += ft_putunbr(va_arg(args, unsigned int));
	else if (specifier == 'x')
		i += ft_puthex(va_arg(args, unsigned int), 0);
	else if (specifier == 'X')
		i += ft_puthex(va_arg(args, unsigned int), 1);
	else if (specifier == '%')
		i += ft_putchar('%');
	return (i);
}
