/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:20:00 by dvan-hem          #+#    #+#             */
/*   Updated: 2024/11/05 13:18:47 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dup;

	i = 0;
	while (s1[i] != '\0')
		i++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char src[] = "Kakou Kakou!";
	char *dup = ft_strdup(src);

	if (dup == NULL)
	{
		printf("Malloc failed!");
		return (1);
	}
	printf("Og string: %s\n", src);
	printf("Duplicated: %s\n", dup);
	free(dup);
	return (0);
}*/
