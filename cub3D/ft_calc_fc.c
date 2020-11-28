/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clac.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:41:10 by hoylee            #+#    #+#             */
/*   Updated: 2020/11/28 22:21:03 by hoylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_macos.h"

void	ft_set_fc(t_info *info, float *fl_step_xy, int y, float *floor_xy)
{
	float		raydir_xx[2];
	float		raydir_yy[2];
	float		rowDistance;

	raydir_xx[0] = info->dirX - info->planeX;
	raydir_xx[1] = info->dirX + info->planeX;
	raydir_yy[0] = info->dirY - info->planeY;
	raydir_yy[1] = info->dirY + info->planeY;
	rowDistance = (0.5 * info->height) / (y - info->height / 2);
	fl_step_xy[0] = rowDistance
					* (raydir_xx[1] - raydir_xx[0]) / info->width;
	fl_step_xy[1] = rowDistance
					* (raydir_yy[1] - raydir_yy[0]) / info->width;
	floor_xy[0] = info->posX + rowDistance * raydir_xx[0];
	floor_xy[1] = info->posY + rowDistance * raydir_yy[0];
}

void	ft_colr_fc(t_info *info, float *floor_xy, float *fl_step_xy, int y)
{
	int x;
	int color;
	int tx;
	int ty;

	x = 0;
	while (x < info->width)
	{
		tx = (int)(info->texture_x_size
			* (floor_xy[0] - (int)(floor_xy[0]))) & (info->texture_x_size - 1);
		ty = (int)(info->texture_y_size
			* (floor_xy[1] - (int)(floor_xy[1]))) & (texHeight - 1);
		floor_xy[0] += fl_step_xy[0];
		floor_xy[1] += fl_step_xy[1];
		color = info->texture[5][info->texture_x_size * ty + tx];
		color = (color / 2) & 8355711;
		info->buf[y][x] = color;
		color = info->texture[6][info->texture_x_size * ty + tx];
		color = (color / 2) & 8355711;
		info->buf[info->height - y - 1][x] = color;
		x++;
	}
}

int		ft_calc_fc(t_info *info)
{
	float		fl_step_xy[2];
	float		floor_xy[2];
	int			y;

	y = info->height / 2 + 1;
	while (y < info->height)
	{
		ft_set_fc(info, fl_step_xy, y, floor_xy);
		ft_colr_fc(info, floor_xy, fl_step_xy, y);
		y++;
	}
	return (0);
}
