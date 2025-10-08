/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauafth <asauafth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 08:12:26 by asauafth          #+#    #+#             */
/*   Updated: 2025/10/06 00:22:07 by asauafth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	read_map(char *map, char ***parsed, int count)
{
	int	i;
	int	fd;
	int	len;

	fd = open(map, O_RDONLY);
	i = 0;
	if (fd < 0)
		return (1);
	while (i < count)
	{
		(*parsed)[i] = get_next_line(fd);
		if (!(*parsed)[i])
		{
			clean_map(*parsed);
			close(fd);
			return (1);
		}
		len = ft_strlen_so_long((*parsed)[i]);
		if (len > 0 && (*parsed)[i][len - 1] == '\n')
			(*parsed)[i][len - 1] = '\0';
		i++;
	}
	close(fd);
	(*parsed)[i] = NULL;
	return (0);
}

int	count_lines(int fd)
{
	int		count;
	char	*line;

	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}


/*******************************************************************/
/*      here we will check if have  unreachable_element            */
/*      we will use all the above function to check                */
/*******************************************************************/

int	unreachable_element(char **map, int rows)
{
	char	**mock_map;
	int		player_x;
	int		palyer_y;

	player_x = 0;
	palyer_y = 0;
	mock_map = mock_map_(map, rows);
	if (!mock_map)
		return (1);
	find_player(mock_map, &player_x, &palyer_y);
	flood_fill(mock_map, player_x, palyer_y);
	if (not_flooded(mock_map))
	{
		ft_printf("Error: unreachable element found. Fix the map.\n");
		clean_map(mock_map);
		return (1);
	}
	clean_map(mock_map);
	return (0);
}
