/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:53:20 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/10 13:27:04 by ybahri           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

static int	vec_init(char ***arr, int *cap)
{
	if (*cap != 0)
		return (1);
	*cap = 32;
	*arr = (char **)ft_calloc(*cap, sizeof(char *));
	if (!*arr)
		return (0);
	return (1);
}

static int	vec_grow(char ***arr, int *cap, int len)
{
	char	**tmp;
	int		i;
	int		nc;

	if (len < *cap)
		return (1);
	nc = (*cap) * 2;
	tmp = (char **)ft_calloc(nc, sizeof(char *));
	if (!tmp)
		return (0);
	i = 0;
	while (i < *cap)
	{
		tmp[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	*arr = tmp;
	*cap = nc;
	return (1);
}

int	push_line(char ***arr, int *len, int *cap, char *owned)
{
	if (!vec_init(arr, cap))
		return (0);
	if (!vec_grow(arr, cap, *len))
		return (0);
	(*arr)[*len] = owned;
	(*len)++;
	return (1);
}
