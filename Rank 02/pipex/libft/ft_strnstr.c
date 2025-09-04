/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:35:32 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/07/27 04:08:28 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	to_find_len;
	size_t	i;

	i = 0;
	if (haystack == NULL)
		return (NULL);
	to_find_len = ft_strlen(needle);
	if (to_find_len == 0)
		return ((char *)haystack);
	if (len < to_find_len)
		return (NULL);
	while (haystack[i] && i <= len - to_find_len)
	{
		if (ft_strncmp(haystack + i, needle, to_find_len) == 0)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
// #include <string.h>
// #include <stdio.h>

// int	main()
// {
// 	printf("Test strnstr with NULL\n");
// 	// ft_strnstr(NULL,NULL, 10);
// 	ft_strnstr(((void *)0), "fake", 3);
// 	return (0);
// }