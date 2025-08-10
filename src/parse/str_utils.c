/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:46:39 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/10 12:49:54 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_spaces_i(const char *s, int i)
{
	while(s[i] == ' ' || s[i] == '\t')
		i++;
	return(i);
}

int	is_blank_line(const char *s)
{
	int	i;

	i = 0;
	while ( s[i] == ' ' || s[i] == '\t' )
		i++;
	return (s[i] == '\0');
}

int	ends_with_xpm(const char *p)
{
	size_t	l;

	l = ft_strlen(p);
	if (l < 4)
		return (0);
	return (p[l - 4] == '.' && p[l - 3] == 'x' && p[l - 2] == 'p' && p[l - 1] == 'm');
}

int	is_map_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == PLAYER_N || c == PLAYER_S || c == PLAYER_E || c == PLAYER_W)
		return (1);
	return (0);
}

int	is_map_line_or_blank(const char *s)
{
	int	i;

	if (s[0] == '\0')
		return (1);
	i = 0;
	while (s[i] != '\0')
	{
		if (!is_map_char(s[i]))
			return (0);
		i++;
	}
	return (1);
}
