/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:54:14 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/10 12:54:16 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**pad_map_rect(t_cub_config *cfg, int *pw, int *ph)
{
	int		y;
	int		x;
	char	**pad;

	*pw = cfg->map_width + 2;
	*ph = cfg->map_height + 2;
	pad = (char **)ft_calloc(*ph, sizeof(char *));
	if (!pad)
		return (NULL);
	y = 0;
	while (y < *ph)
	{
		pad[y] = (char *)ft_calloc(*pw + 1, sizeof(char));
		if (!pad[y])
			return (NULL);
		x = 0;
		while (x < *pw)
		{
			pad[y][x] = ' ';
			x++;
		}
		pad[y][*pw] = '\0';
		y++;
	}
	return (pad);
}

void	copy_into_pad(t_cub_config *cfg, char **pad)
{
	int	y;
	int	x;

	y = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		while (cfg->map[y][x])
		{
			pad[y + 1][x + 1] = cfg->map[y][x];
			x++;
		}
		y++;
	}
}
