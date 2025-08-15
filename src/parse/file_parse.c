/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:55:17 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/15 03:12:20 by ybahri           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

int	all_headers_ready(t_cub_config *cfg, int seen)
{
	int	need;

	need = (1 << TEX_NO) | (1 << TEX_SO) | (1 << TEX_EA)
		| (1 << TEX_WE) | (1 << 4) | (1 << 5);
	if ((seen & need) != need)
		return (put_error("Missing elements (NO/SO/EA/WE and/or F/C)"), 0);
	if (cfg->floor_color < 0 || cfg->ceiling_color < 0)
		return (put_error("Invalid colors"), 0);
	return (1);
}

static int	process_before_map(char *line, int *started, int *seen, t_cub_config *cfg)
{
	int	r;

	if (is_blank_line(line))
		return (1);
	r = parse_header_line(line, cfg, seen);
	if (r == -1 && is_map_line_or_blank(line))
	{
		if (!all_headers_ready(cfg, *seen))
			return (0);
		*started = 1;
		return (1);
	}
	if (r == 0)
		return (0);
	return (1);
}

static int	process_map_line(char *line, char ***map, int *mlen, int *mcap)
{
    if (is_blank_line(line))
        return (put_error(ERROR_MAP_EMPTY_LINE), 0);
    if	(!is_map_line_or_blank(line))
        return (put_error("Only map content after it starts"), 0);
    if(!push_line(map, mlen, mcap, line))
        return (put_error("Allocation failed"), 0);
    return (1);
}

static int	read_all(int fd, t_cub_config *cfg, char ***map, int *mlen)
{
	char	*line;
	int		mcap;
	int		seen;
	int		started;

	mcap = 0;
	seen = 0;
	started = 0;
	*mlen = 0;
	*map = NULL;
	cfg->floor_color = -1;
	cfg->ceiling_color = -1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!started)
		{
			if (!process_before_map(line, &started, &seen, cfg))
				return (0);
			if (!started)
			{
				free(line);
				continue ;
			}
		}
		if (!process_map_line(line, map, mlen, &mcap))
			return (0);
	}
	if (!started)
		return (put_error("Missing map"), 0);
	return (1);
}

t_cub_config	*parse_cub_file(const char *filename)
{
	int				fd;
	t_cub_config	*cfg;
	char			**lines;
	int				len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (put_error("Cannot open .cub"), NULL);
	cfg = (t_cub_config *)ft_calloc(1, sizeof(t_cub_config));
	if (!cfg)
		return (put_error("Allocation failed"), NULL);
	lines = NULL;
	len = 0;
	if (!read_all(fd, cfg, &lines, &len))
		return (free_cub_config(cfg), close(fd), NULL);
	close(fd);
	if (!build_map_from_lines(cfg, lines, len))
		return (free_cub_config(cfg), NULL);
	if (!validate_single_player(cfg))
		return (free_cub_config(cfg), NULL);
	if (!validate_map_closed(cfg))
		return (free_cub_config(cfg), NULL);
	return (cfg);
}
