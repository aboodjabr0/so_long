/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauafth <asauafth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:01:00 by asauafth          #+#    #+#             */
/*   Updated: 2025/10/05 15:03:41 by asauafth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sound.h"

void	clean_numbers(t_physicals *imgs, void *mlx)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (imgs->numbers[i])
			mlx_destroy_image(mlx, imgs->numbers[i]);
		i++;
	}
}

void	clean_player_imgs(t_physicals *imgs, void *mlx)
{
	if (imgs->looking_down)
		mlx_destroy_image(mlx, imgs->looking_down);
	if (imgs->looking_up)
		mlx_destroy_image(mlx, imgs->looking_up);
	if (imgs->looking_left)
		mlx_destroy_image(mlx, imgs->looking_left);
	if (imgs->looking_right)
		mlx_destroy_image(mlx, imgs->looking_right);
}

void	null_imgs(t_physicals *imgs)
{
	int	i;

	i = 0;
	imgs->block = NULL;
	imgs->floor = NULL;
	imgs->closed_d = NULL;
	imgs->opened_d = NULL;
	imgs->looking_down = NULL;
	imgs->looking_up = NULL;
	imgs->looking_left = NULL;
	imgs->looking_right = NULL;
	imgs->ghost1 = NULL;
	imgs->ghost2 = NULL;
	imgs->ghost3 = NULL;
	imgs->ghost4 = NULL;
	imgs->collectibles = NULL;
	while (i < 10)
	{
		imgs->numbers[i] = NULL;
		i++;
	}
}

void	clean_imgs(t_physicals *imgs, void *mlx)
{
	if (imgs->block)
		mlx_destroy_image(mlx, imgs->block);
	if (imgs->floor)
		mlx_destroy_image(mlx, imgs->floor);
	if (imgs->closed_d)
		mlx_destroy_image(mlx, imgs->closed_d);
	if (imgs->opened_d)
		mlx_destroy_image(mlx, imgs->opened_d);
	if (imgs->ghost1)
		mlx_destroy_image(mlx, imgs->ghost1);
	if (imgs->ghost2)
		mlx_destroy_image(mlx, imgs->ghost2);
	if (imgs->ghost3)
		mlx_destroy_image(mlx, imgs->ghost3);
	if (imgs->ghost4)
		mlx_destroy_image(mlx, imgs->ghost4);
	if (imgs->collectibles)
		mlx_destroy_image(mlx, imgs->collectibles);
	clean_player_imgs(imgs, mlx);
	clean_numbers(imgs, mlx);
	null_imgs(imgs);
}

int	close_game(t_game *pac_man)
{
	if (!pac_man)
		return (1);
	sound_stop_music();
	if (pac_man->window)
		mlx_destroy_window(pac_man->mlx, pac_man->window);
	clean_map(pac_man->map);
	clean_imgs(&pac_man->imgs, pac_man->mlx);
	if (pac_man->mlx)
	{
		mlx_destroy_display(pac_man->mlx);
		free(pac_man->mlx);
	}
	pac_man->mlx = NULL;
	pac_man->map = NULL;
	pac_man->width = 0;
	pac_man->height = 0;
	exit(EXIT_SUCCESS);
	return (0);
}
