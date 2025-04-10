/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:44:13 by dvan-hem          #+#    #+#             */
/*   Updated: 2024/11/11 12:30:59 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (res > LLONG_MAX && sign == 1)
		return (-1);
	if (res > LLONG_MAX && sign == -1)
		return (0);
	return (res * sign);
}
// #include <stdio.h>
// #include <stdlib.h>
// //  + METTRE RES EN UNSIGNED LONG LONG ET PAS INT
// int main(void)
// {
// 	char *str = "     -123fsj456";
// 	char *str1 = "		+123456sgu789";
// 	char *str2 = "     +-123d4";
// 	char *str3 = "    --123456fk";
// 	char *str4 = "-9223372036854775807";
// 	char *str5 = "9223372036854775808";

// 	printf("Res: \"%s\" --> %d\n", str, ft_atoi(str));
// 	printf("Res: \"%s\" --> %d\n", str, atoi(str));
// 	printf("Res: \"%s\" --> %d\n", str1, ft_atoi(str1));
// 	printf("Res: \"%s\" --> %d\n", str1, atoi(str1));
// 	printf("Res: \"%s\" --> %d\n", str2, ft_atoi(str2));
// 	printf("Res: \"%s\" --> %d\n", str2, atoi(str2));
// 	printf("Res: \"%s\" --> %d\n", str3, ft_atoi(str3));
// 	printf("Res: \"%s\" --> %d\n", str3, atoi(str3));
// 	printf("res: \"%s\" --> %d\n", str4, ft_atoi(str4));
// 	printf("res: \"%s\" --> %d\n", str4, atoi(str4));
// 	printf("res: \"%s\" --> %d\n", str5, ft_atoi(str5));
// 	printf("res: \"%s\" --> %d\n", str5, atoi(str5));
// 	return (0);
// }
