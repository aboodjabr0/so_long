/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauafth <asauafth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:04:31 by asauafth          #+#    #+#             */
/*   Updated: 2025/10/08 10:59:43 by asauafth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sound.h"

void	re_render(t_game *pac_man)
{
	pac_man->map[pac_man->player.y][pac_man->player.x] = '0';
	if (pac_man->exit_x == pac_man->player.x
		&& pac_man->exit_y == pac_man->player.y)
		pac_man->map[pac_man->player.y][pac_man->player.x] = 'E';
}

int	blocked(t_game *pacman, int new_x, int new_y)
{
	int	rows;
	int	cols;

	rows = pacman->height / IMG_H;
	cols = pacman->width / IMG_W;
	if (new_x < 0 || new_y < 0 || new_x >= cols || new_y >= rows)
		return (1);
	if (pacman->map[new_y][new_x] == '1')
		return (1);
	return (0);
}

void	attempt_move(t_game *pacman, int current_x, int current_y, int dir)
{
	int			new_x;
	int			new_y;
	char		tile;

	new_x = pacman->player.x + current_x;
	new_y = pacman->player.y + current_y;
	if (blocked(pacman, new_x, new_y))
		return ;
	tile = pacman->map[new_y][new_x];
	pacman->player.dir = dir;
	if (tile == 'C')
	{
		pacman->collected++;
	play_sound_async("assets/sounds/collected.wav");
	}
	re_render(pacman);
	pacman->player.x = new_x;
	pacman->player.y = new_y;
	pacman->player.moves++;
	ft_printf("Moves: %d\n", pacman->player.moves);
	end_game(pacman, tile);
	pacman->map[new_y][new_x] = 'P';
	render_game(pacman);
}

int	pac_keys(int keycode, t_game *pac_man)
{
	if (keycode == 65362 || keycode == 119)
		attempt_move(pac_man, 0, -1, DIR_UP);
	else if (keycode == 65364 || keycode == 115)
		attempt_move(pac_man, 0, 1, DIR_DOWN);
	else if (keycode == 65361 || keycode == 97)
		attempt_move(pac_man, -1, 0, DIR_LEFT);
	else if (keycode == 65363 || keycode == 100)
		attempt_move(pac_man, 1, 0, DIR_RIGHT);
	else if (keycode == 65307)
		close_game(pac_man);
	return (0);
}
