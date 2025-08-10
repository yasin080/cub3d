/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:50:18 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/10 12:50:55 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_component(const char *s, int *i, int *out)
{
	long	n;

	n = 0;
	if (!ft_isdigit(s[*i]))
		return (0);
	while (ft_isdigit(s[*i]))
	{
		n = n * 10 + (s[*i] - '0');
		if (n > 255)
			return (0);
		(*i)++;
	}
	*out = (int)n;
	return (1);
}

int	parse_rgb_triplet(const char *p, int *out)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	i = skip_spaces_i(p, i);
	if (!parse_component(p, &i, &r))
		return (0);
	i = skip_spaces_i(p, i);
	if (p[i] != ',')
		return (0);
	i++;
	i = skip_spaces_i(p, i);
	if (!parse_component(p, &i, &g))
		return (0);
	i = skip_spaces_i(p, i);
	if (p[i] != ',')
		return (0);
	i++;
	i = skip_spaces_i(p, i);
	if (!parse_component(p, &i, &b))
		return (0);
	i = skip_spaces_i(p, i);
	if (p[i] != '\0')
		return (0);
	*out = (r << 16) | (g << 8) | b;
	return (1);
}
