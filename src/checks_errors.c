/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:56:10 by alejanr2          #+#    #+#             */
/*   Updated: 2025/08/10 15:28:53 by ybahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_extension(const char *filename)
{
    int	len;

    len = 0;
    while (filename[len])
        len++;
    if (len < 4)
        return (0);
    return (filename[len - 4] == '.' && filename[len - 3] == 'c'
        && filename[len - 2] == 'u' && filename[len - 1] == 'b');
}

// Comprueba todos los errores iniciales y retorna 0 si hay error, 1 si todo OK
int	checksAllErrors(int argc, char **argv, t_cub_config **cfg, t_mlx **mlx)
{
	if (argc != 2)
		return (printf(ERROR_ARGUMENTOS), 0);
	if (!validate_extension(argv[1]))
		return (printf(ERROR_EXTENSION), 0);

	*cfg = parse_cub_file(argv[1]);
	if (!*cfg)
		return(0);
		//return (printf(ERROR_PARSEO), 0);

	*mlx = init_window(*cfg);
	if (!*mlx)
	{
		free_cub_config(*cfg);
		return (printf(ERROR_MLX), 0);
	}
	return (1);
}
