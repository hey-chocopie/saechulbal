/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoylee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:42:18 by hoylee            #+#    #+#             */
/*   Updated: 2020/11/23 14:00:18 by hoylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./mlxfolder/mlx.h"
#include "key_macos.h"
#include "./printf/ft_printf.h"

void    ft_input_texture_free(t_info *info)
{
    if(info->no_texture != 0)
    {
        free(info -> no_texture);
        info->no_texture = 0;
    }
    if(info->so_texture != 0)
    {
        free(info -> so_texture);
        info->so_texture = 0;
    }
    if(info->we_texture != 0)
    {
        free(info -> we_texture);
        info->we_texture = 0;
    }
    if(info->ea_texture != 0)
    {
        free(info -> ea_texture);
        info->ea_texture = 0;
    }
    if(info->s_texture != 0)
    {
        free(info -> s_texture);
        info->s_texture = 0;
    }
    if(info->ft_texture != 0)
    {
        free(info -> ft_texture);
        info->ft_texture = 0;
    }
    if(info->ct_texture != 0)
    {
        free(info -> ct_texture);
        info->ct_texture = 0;
    }
}

void	ft_tool_mem_free(t_info *info)
{
	int i = -1;
	ft_input_texture_free(info);
	while(++i < info->width)
		free(info->buf[i]);
	ft_printf("%d : %s", 12, strerror(-12));
}
