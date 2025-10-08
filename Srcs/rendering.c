/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauafth <asauafth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 01:06:54 by asauafth          #+#    #+#             */
/*   Updated: 2025/10/05 22:47:42 by asauafth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	stick_image(t_game *pac_man, void *img, int grid_x, int grid_y)
{
	if (!img)
		return ;
	mlx_put_image_to_window(pac_man->mlx, pac_man->window, img, grid_x * IMG_W,
		grid_y * IMG_H);
}

void	render_game(t_game *pac_man)
{
	int		y;
	int		x;
	char	tile;

	y = 0;
	while (y < pac_man->height / IMG_H)
	{
		x = 0;
		while (x < pac_man->width / IMG_W)
		{
			stick_image(pac_man, pac_man->imgs.floor, x, y);
			tile = pac_man->map[y][x];
			render_img(pac_man, tile, y, x);
			x++;
		}
		y++;
	}
	render_moves(pac_man);
}

void	render_player(t_game *pac_man, int y, int x)
{
	void	*img;

	img = NULL;
	if (pac_man->player.dir == DIR_UP)
		img = pac_man->imgs.looking_up;
	if (pac_man->player.dir == DIR_DOWN)
		img = pac_man->imgs.looking_down;
	if (pac_man->player.dir == DIR_LEFT)
		img = pac_man->imgs.looking_left;
	if (pac_man->player.dir == DIR_RIGHT)
		img = pac_man->imgs.looking_right;
	stick_image(pac_man, img, x, y);
}

void	render_img(t_game *pac_man, char type, int y, int x)
{
	void	*ghost;

	if (type == '1')
		stick_image(pac_man, pac_man->imgs.block, x, y);
	else if (type == 'C')
		stick_image(pac_man, pac_man->imgs.collectibles, x, y);
	else if (type == 'E')
	{
		if (pac_man->collectables == pac_man->collected)
			stick_image(pac_man, pac_man->imgs.opened_d, x, y);
		else
			stick_image(pac_man, pac_man->imgs.closed_d, x, y);
	}
	else if (type == 'P')
		render_player(pac_man, y, x);
	else if (type == 'R')
	{
		ghost = select_ghost_sprite(pac_man, (y * 31 + x));
		if (ghost)
			stick_image(pac_man, ghost, x, y);
	}
}

void	render_moves(t_game *pacman)
{
	int	i;
	int	moves;
	int	digits[10];
	int	count;

	i = 0;
	count = 0;
	moves = pacman->player.moves;
	if (moves == 0)
	{
		stick_image(pacman, pacman->imgs.numbers[0], 0, 0);
		return ;
	}
	while (moves > 0 && count < 10)
	{
		digits[count++] = moves % 10;
		moves /= 10;
	}
	while (count-- > 0)
		stick_image(pacman, pacman->imgs.numbers[digits[count]], i++, 0);
}
