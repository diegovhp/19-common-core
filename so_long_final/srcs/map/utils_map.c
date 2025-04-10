/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:57:08 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/05 15:41:35 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

int	map_height(char **map)
{
	int	h;

	h = 0;
	while (map[h])
		h++;
	return (h);
}

int	map_width(char **map)
{
	if (!map || !map[0])
		return (0);
	return (ft_strlen(map[0]));
}
