/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauafth <asauafth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:22:46 by asauafth          #+#    #+#             */
/*   Updated: 2025/10/08 10:59:44 by asauafth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <mlx.h>
#include "so_long.h"
#include "sound.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_game	pac_man;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: %s <map.ber>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	ft_memset(&pac_man, 0, sizeof(t_game));
	validate_file(argc, argv[1]);
	if (start_game(&pac_man, argv[1]))
	{
		ft_printf("ERROR\nFailed to launch game\n");
		close_game(&pac_man);
		return (1);
	}
	sound_start_music("assets/sounds/pacman.wav");
	render_game(&pac_man);
	mlx_hook(pac_man.window, 2, 1L << 0, &pac_keys, &pac_man);
	mlx_hook(pac_man.window, 17, 0, close_game, &pac_man);
	mlx_loop(pac_man.mlx);
	return (0);
}
