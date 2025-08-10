/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:18:18 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/10 13:30:16 by ybahri           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

// Carga una textura XPM con MLX desde 'path'.
static t_texture	load_one(const char *path, t_mlx *mlx)
{
	t_texture	tex;
	int			bpp;
	int			line_len;
	int			endian;

	tex.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, (char *)path,
			&tex.width, &tex.height);
	if (!tex.img_ptr)
	{
		put_error("mlx failed to load texture");
		exit(1);
	}
	tex.buffer = (int *)mlx_get_data_addr(tex.img_ptr, &bpp, &line_len,
			&endian);
	if (!tex.buffer)
	{
		put_error("mlx_get_data_addr failed");
		exit(1);
	}
	return (tex);
}

// Carga todas las texturas de paredes usando las rutas del archivo .cub
void	load_textures(t_mlx *mlx, t_cub_config *cfg)
{
	if (!cfg->tex_path[TEX_NO] || !cfg->tex_path[TEX_SO]
		|| !cfg->tex_path[TEX_EA] || !cfg->tex_path[TEX_WE])
	{
		put_error("Missing texture paths");
		exit(1);
	}
	cfg->textures[TEX_NO] = load_one(cfg->tex_path[TEX_NO], mlx);
	cfg->textures[TEX_SO] = load_one(cfg->tex_path[TEX_SO], mlx);
	cfg->textures[TEX_EA] = load_one(cfg->tex_path[TEX_EA], mlx);
	cfg->textures[TEX_WE] = load_one(cfg->tex_path[TEX_WE], mlx);
}
