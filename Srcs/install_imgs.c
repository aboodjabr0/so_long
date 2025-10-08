/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   install_imgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauafth <asauafth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:26:31 by asauafth          #+#    #+#             */
/*   Updated: 2025/10/08 10:59:41 by asauafth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void spawn_player(t_player *player, char **map)
{
    player -> moves = 0;
    player -> dir = DIR_DOWN;
    find_player(map, &player -> x, &player -> y);
}
void deploy_player(t_physicals *imgs, void *mlx)
{
    int w;
    int h;

    w = imgs->width;
    h = imgs->height;
    imgs->looking_up = mlx_xpm_file_to_image(mlx, "assets/textures/up.xpm", &w, &h);
    imgs->looking_down = mlx_xpm_file_to_image(mlx, "assets/textures/down.xpm", &w, &h);
    imgs->looking_left = mlx_xpm_file_to_image(mlx, "assets/textures/left.xpm", &w, &h);
    imgs->looking_right = mlx_xpm_file_to_image(mlx, "assets/textures/right.xpm", &w, &h);
}

void load_number_imgs(t_physicals *imgs, void *mlx)
{
    int i;
    int w;
    int h;
    char path[] = "assets/textures/0.xpm";

    i = 0;
    w = imgs->width;
    h = imgs->height;
    while (i < 10)
    {
    path[16] = '0' + i;
        imgs->numbers[i] = mlx_xpm_file_to_image(mlx, path, &w, &h);
        i++;
    }
}

int	check_imgs(t_physicals *imgs)
{
	if (!imgs->closed_d || !imgs->opened_d || !imgs->block
    || !imgs->floor || !imgs->collectibles || !imgs->ghost1 || !imgs->ghost2
    || !imgs->ghost3 || !imgs->ghost4 
    || player_is_null(imgs) || img_is_null(imgs))
	{
		return (1);
	}
    return (0);
}
int deploy_imgs(t_physicals *imgs, void *mlx)
{
    imgs->height = IMG_H;
    imgs->width = IMG_W;
    imgs->closed_d = mlx_xpm_file_to_image(mlx, "assets/textures/closed_d.xpm",
        &imgs->width, &imgs->height);
    imgs->opened_d = mlx_xpm_file_to_image(mlx, "assets/textures/open_d.xpm", 
        &imgs->width, &imgs->height);
    imgs->block = mlx_xpm_file_to_image(mlx, "assets/textures/block.xpm", 
        &imgs->width, &imgs->height);
    imgs->floor = mlx_xpm_file_to_image(mlx, "assets/textures/floor.xpm", 
        &imgs->width, &imgs->height);
    imgs->collectibles = mlx_xpm_file_to_image(mlx, "assets/textures/collectible.xpm", 
        &imgs->width, &imgs->height);
    imgs->ghost1 = mlx_xpm_file_to_image(mlx, "assets/textures/ghost1.xpm", 
        &imgs->width, &imgs->height);
    imgs->ghost2 = mlx_xpm_file_to_image(mlx, "assets/textures/ghost2.xpm", 
        &imgs->width, &imgs->height);
    imgs->ghost3 = mlx_xpm_file_to_image(mlx, "assets/textures/ghost3.xpm", 
        &imgs->width, &imgs->height);
    imgs->ghost4 = mlx_xpm_file_to_image(mlx, "assets/textures/ghost4.xpm", 
        &imgs->width, &imgs->height);
    deploy_player(imgs, mlx);
    load_number_imgs(imgs, mlx);
        return (check_imgs(imgs));
}
