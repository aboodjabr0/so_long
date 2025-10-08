/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauafth <asauafth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:24:13 by marvin            #+#    #+#             */
/*   Updated: 2025/10/08 10:02:51 by asauafth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/***********************************************************************/
/*   if the map is correctly structured we need to check if its valid  */
/*   soo in this file we check if the map is following the rules       */
/***********************************************************************/

#include "so_long.h"

int	is_not_rectangular(char **map, int columns)
{
	int	i;

	i = 1;
	while (map[i])
	{
		if ((int)ft_strlen_so_long(map[i]) != columns)
		{
			ft_printf("Error: map is not rectangular\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	gaps_check(char **map, int columns, int rows)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1' || map[rows - 1][i] != '1')
		{
			ft_printf("Error: map must be closed by walls (top/bottom)\n");
			return (1);
		}
		i++;
	}
	i = 1;
	while (i < rows - 1)
	{
		if (map[i][0] != '1' || map[i][columns - 1] != '1')
		{
			ft_printf("Error: map must be closed by walls (sides)\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_invalid_chars(char **map, int columns, int rows)
{
	int	i;
	int	j;

	i = 1;
	while (i < rows - 1)
	{
		j = 1;
		while (j < columns - 1)
		{
			if (!ft_strchr("10PECR", map[i][j]))
			{
				ft_printf("Error: invalid character '%c' found\n", map[i][j]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_counters(char **map)
{
	int	player_count;
	int	exits_count;
	int	collectibles_count;
	int rows;
	int columns;

	player_count = 0;
	exits_count = 0;
	map_measurements(map, &rows, &columns);
	collectibles_count = count_collectibles(map);
	check_map_tools(map, rows, columns, &player_count, &exits_count);
	if (player_count != 1 || exits_count != 1 || collectibles_count < 1)
	{
		ft_printf("the map should have only 1 player,"
			"1 exit\n and at least 1 collectible");
		return (1);
	}
	return (0);
}

int	is_the_map_valid(char **map)
{
	int	columns;
	int	rows;

	if (!map || !map[0])
		return (1);
	map_measurements(map, &rows, &columns);
	if (is_not_rectangular(map, columns) || gaps_check(map, columns, rows)
		|| check_invalid_chars(map, columns, rows) || check_counters(map)
		|| unreachable_element(map, rows))
		return (1);
	return (0);
}
