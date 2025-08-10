/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/10 13:03:34 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_cub_config(t_cub_config *cfg)
{
	int	i;

	if (!cfg)
		return ;
	i = 0;
	while (i < TEX_COUNT)
	{
		if (cfg->tex_path[i])
			free(cfg->tex_path[i]);
		i++;
	}
	if (cfg->map)
	{
		i = 0;
		while (i < cfg->map_height)
		{
			if (cfg->map[i])
				free(cfg->map[i]);
			i++;
		}
		free(cfg->map);
	}
	free(cfg);
}
