/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/15 02:18:18 by ybahri           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

// Función que se ejecuta cuando se cierra la ventana
int	close_window(t_mlx *mlx)
{
	destroy_window(mlx);
	exit(0);
}

static int	init_framebuffer(t_mlx *mlx)
{
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->width, mlx->height);
	if (!mlx->img_ptr)
		return (0);
	mlx->pixels = (int *)mlx_get_data_addr(mlx->img_ptr, &mlx->bpp,
			&mlx->line_len, &mlx->endian);
	if (!mlx->pixels)
		return (0);
	return (1);
}

t_mlx	*init_window(const t_cub_config *cfg)
{
	t_mlx	*mlx;

	(void)cfg;
	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->width = 800;
	mlx->height = 600;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
	{
		free(mlx);
		return (NULL);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->width, mlx->height,
			"cub3D");
	if (!mlx->win_ptr)
	{
		free(mlx);
		return (NULL);
	}
	if (!init_framebuffer(mlx))
	{
		destroy_window(mlx);
		return (NULL);
	}
	mlx_hook(mlx->win_ptr, 33, 1L << 17, close_window, mlx);
	return (mlx);
}

void	destroy_window(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->img_ptr && mlx->mlx_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	if (mlx->win_ptr && mlx->mlx_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	free(mlx);
}
