/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahri <ybahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:41:29 by ybahri            #+#    #+#             */
/*   Updated: 2025/08/15 01:16:57 by ybahri           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

static void	write_str(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	if (i > 0)
		write(2, s, i);
}

void	put_error(const char *msg)
{
	write(2, "Error\n", 7);
	write_str(msg);
	write(2, "\n", 1);
}
