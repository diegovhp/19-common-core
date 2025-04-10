/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:43:57 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/01/07 15:55:39 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, format);
	if (format == NULL)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			count += ft_format(args, format[++i]);
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
