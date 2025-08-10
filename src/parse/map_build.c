/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:53:41 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/10 12:53:43 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_players_line(const char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == PLAYER_N || s[i] == PLAYER_S
			|| s[i] == PLAYER_E || s[i] == PLAYER_W)
			n++;
		i++;
	}
	return (n);
}

static int	validate_line_chars(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_map_char(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	build_map_from_lines(t_cub_config *cfg, char **lines, int len)
{
	int	i;
	int	w;

	cfg->map = (char **)ft_calloc(len, sizeof(char *));
	if (!cfg->map)
		return (put_error("Allocation failed"), 0);
	cfg->map_height = len;
	cfg->map_width = 0;
	i = 0;
	while (i < len)
	{
		if (!validate_line_chars(lines[i]))
			return (put_error("Invalid character in map"), 0);
		cfg->map[i] = lines[i];
		w = (int)ft_strlen(lines[i]);
		if (w > cfg->map_width)
			cfg->map_width = w;
		i++;
	}
	return (1);
}

int	validate_single_player(t_cub_config *cfg)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (i < cfg->map_height)
	{
		total += count_players_line(cfg->map[i]);
		i++;
	}
	if (total != 1)
		return (put_error("There must be exactly one player"), 0);
	return (1);
}
