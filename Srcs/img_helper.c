/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauafth <asauafth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:35:42 by asauafth          #+#    #+#             */
/*   Updated: 2025/10/05 22:41:11 by asauafth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int img_is_null(t_physicals *imgs)
{
    int i;

    i = 0;
    while (i < 10)
    {
        if (!imgs->numbers[i])
            return (1);
        i++;
    }
    return (0);
}
int player_is_null(t_physicals *imgs)
{
    if (!imgs->looking_down || !imgs->looking_left
        || !imgs->looking_up || !imgs->looking_right)
        return (1);
    return (0);
}

void	*select_ghost_sprite(t_game *pac_man, int seq)
{
	void	*ghosts[4];
	int		available;

	ghosts[0] = pac_man->imgs.ghost1;
	ghosts[1] = pac_man->imgs.ghost2;
	ghosts[2] = pac_man->imgs.ghost3;
	ghosts[3] = pac_man->imgs.ghost4;
	available = 0;
	while (available < 4 && ghosts[available])
		available++;
	if (available == 0)
		return (NULL);
	return (ghosts[seq % available]);
}