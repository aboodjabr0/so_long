/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauafth <asauafth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 22:49:33 by asauafth          #+#    #+#             */
/*   Updated: 2025/10/05 23:35:03 by asauafth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <time.h>

char **parse_map(char *map)
{
    char **parsed;
    int fd;
    int count;

    fd = open(map, O_RDONLY);
    if (fd < 0)
        return (NULL);
    count = count_lines(fd);
    parsed = malloc(sizeof(char *) * (count + 1));
    if (!parsed || read_map(map, &parsed, count) || is_the_map_valid(parsed))
    {
        clean_map(parsed);
        return (NULL);
    }
    return (parsed);
}

/**********************************************************/
/*   initially  we wont have the measurements of the map  */
/*  so we made a small function to calculate them         */
/**********************************************************/

void	map_measurements(char **map, int *rows, int *columns)
{
	*rows = 0;
	while (map[*rows])
		(*rows)++;
	*columns = (int)ft_strlen_so_long(map[0]);
}
void  locate_exit(t_game *pac_man)
{
    int i;
    int j;
    
    i = 1;
    while (pac_man -> map[i])
    {
        j = 1;
        while (pac_man->map[i][j])
        {
            if (pac_man->map[i][j] == 'E')
            {
                pac_man->exit_y = i;
                pac_man->exit_x = j;
                return ;
            }
            j++;
        }
        i++;
    }
}

int     start_game(t_game *pac_man, char *map)
{
    pac_man->map = parse_map(map);
    if (!pac_man->map)
        return (1);
    pac_man->mlx = mlx_init();
    if (!pac_man->mlx)
        return (1);
    pac_man -> collectables = count_collectibles(pac_man->map);
    locate_exit(pac_man);
    map_measurements(pac_man -> map, &pac_man -> height, &pac_man -> width);
    pac_man -> height *= IMG_H;
    pac_man -> width *= IMG_W;
    spawn_player(&pac_man -> player, pac_man -> map);
    if (pac_man->map[pac_man->player.y][pac_man->player.x] != 'P')
    {
        ft_printf("Error: player not found in map.\n");
        return (1);
    }
    if (deploy_imgs(&pac_man->imgs, pac_man->mlx))
        return(1);
    pac_man->window = mlx_new_window(pac_man->mlx, pac_man->width, pac_man->height, "Pacman");
    if(!pac_man->window)
        return (1);
    return (0);
}
