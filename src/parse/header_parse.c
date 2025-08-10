/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:52:08 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/10 13:58:33 by ybahri           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

static int	set_tex_path(t_cub_config *cfg, int idx, const char *path)
{
	int		fd;
	char	*dup;

	if (cfg->tex_path[idx] != NULL)
		return (put_error("Duplicate texture identifier"), 0);
	if (!ends_with_xpm(path))
		return (put_error("Texture must be .xpm"), 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (put_error("Cannot open texture file"), 0);
	close(fd);
	dup = ft_strdup(path);
	if (!dup)
		return (put_error("Allocation failed"), 0);
	cfg->tex_path[idx] = dup;
	return (1);
}

static int	parse_texture_line(const char *p, t_cub_config *cfg, int *seen)
{
	if (p[0] == 'N' && p[1] == 'O' && (p[2] == ' ' || p[2] == '\t'))
	{
		*seen |= (1 << TEX_NO);
		return (set_tex_path(cfg, TEX_NO, p + 3 + skip_spaces_i(p + 3, 0)));
	}
	if (p[0] == 'S' && p[1] == 'O' && (p[2] == ' ' || p[2] == '\t'))
	{
		*seen |= (1 << TEX_SO);
		return (set_tex_path(cfg, TEX_SO, p + 3 + skip_spaces_i(p + 3, 0)));
	}
	if (p[0] == 'W' && p[1] == 'E' && (p[2] == ' ' || p[2] == '\t'))
	{
		*seen |= (1 << TEX_WE);
		return (set_tex_path(cfg, TEX_WE, p + 3 + skip_spaces_i(p + 3, 0)));
	}
	if (p[0] == 'E' && p[1] == 'A' && (p[2] == ' ' || p[2] == '\t'))
	{
		*seen |= (1 << TEX_EA);
		return (set_tex_path(cfg, TEX_EA, p + 3 + skip_spaces_i(p + 3, 0)));
	}
	return (-1);
}

static int	parse_color_line(const char *p, t_cub_config *cfg, int *seen)
{
	if (p[0] == 'F' && (p[1] == ' ' || p[1] == '\t'))
	{
		if (*seen & (1 << 4))
			return (put_error("Duplicate F color"), 0);
		if (!parse_rgb_triplet(p + 2, &cfg->floor_color))
			return (put_error("Invalid F color"), 0);
		*seen |= (1 << 4);
		return (1);
	}
	if (p[0] == 'C' && (p[1] == ' ' || p[1] == '\t'))
	{
		if (*seen & (1 << 5))
			return (put_error("Duplicate C color"), 0);
		if (!parse_rgb_triplet(p + 2, &cfg->ceiling_color))
			return (put_error("Invalid C color"), 0);
		*seen |= (1 << 5);
		return (1);
	}
	return (-1);
}

int	parse_header_line(const char *line, t_cub_config *cfg, int *seen_mask)
{
	int			i;
	const char	*p;
	int			r;

	i = skip_spaces_i(line, 0);
	p = line + i;
	r = parse_texture_line(p, cfg, seen_mask);
	if (r != -1)
		return (r);
	r = parse_color_line(p, cfg, seen_mask);
	if (r != -1)
		return (r);
	return (-1);
}
