/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:54:51 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/10 12:54:56 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_walkable(char c)
{
	if (c == '0' || c == PLAYER_N || c == PLAYER_S
		|| c == PLAYER_E || c == PLAYER_W)
		return (1);
	return (0);
}

static int	touches_void(char **pad, int x, int y)
{
	if (pad[y - 1][x] == ' ' || pad[y + 1][x] == ' ')
		return (1);
	if (pad[y][x - 1] == ' ' || pad[y][x + 1] == ' ')
		return (1);
	return (0);
}

int	validate_map_closed(t_cub_config *cfg)
{
	int		w;
	int		h;
	int		y;
	int		x;
	char	**pad;

	pad = pad_map_rect(cfg, &w, &h);
	if (!pad)
		return (put_error("Allocation failed"), 0);
	copy_into_pad(cfg, pad);
	y = 1;
	while (y < h - 1)
	{
		x = 1;
		while (x < w - 1)
		{
			if (is_walkable(pad[y][x]) && touches_void(pad, x, y))
				return (put_error("Map is not closed"), 0);
			x++;
		}
		y++;
	}
	return (1);
}
