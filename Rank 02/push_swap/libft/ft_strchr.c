/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:35:44 by dvan-hem          #+#    #+#             */
/*   Updated: 2024/11/11 11:12:02 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	target;

	target = (char)c;
	while (*s != '\0')
	{
		if (*s == target)
			return ((char *)s);
		s++;
	}
	if (target == '\0')
		return ((char *)s);
	return (NULL);
}
// 	if (!s)
// 		return (NULL); après char target
// #include <string.h>
// #include <stdio.h>
// int main()
// {
// 	ft_strchr(NULL,4);
// 	//strchr(NULL, 4);
// }