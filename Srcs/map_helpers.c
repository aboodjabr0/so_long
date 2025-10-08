/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauafth <asauafth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:28:18 by asauafth          #+#    #+#             */
/*   Updated: 2025/10/06 01:06:08 by asauafth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**************************************************************************/
/*     these are functions to help validate the map                       */
/*    their main usage is inside map_validation.c file                    */
/**************************************************************************/

#include "so_long.h"

/*************************************************************/
/*   we use flood fill to check if we have a valid paths     */
/*   and it helps to detect if there is an unreachable item  */
/*************************************************************/

void	flood_fill(char **map, int x, int y)
{
	int	rows;
	int	columns;

	map_measurements(map, &rows, &columns);
	if (x < 0 || y < 0 || x >= columns || y >= rows)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

/*************************************************************/
/*   we need a clean_map function to prevent leaks           */
/*   in case if somthing went wrong while reading            */
/*************************************************************/

void	clean_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
}

/******************************************************************/
/*      flood fill apply changes to the map so we need            */
/*      to give him a copy and thats why we need mock map         */
/******************************************************************/
char	**mock_map_(char **map, int rows)
{
	char	**mock;
	int		i;

	mock = malloc(sizeof(char *) * (rows + 1));
	i = 0;
	if (!mock)
		return (NULL);
	while (i < rows)
	{
		mock[i] = ft_strdup(map[i]);
		if (!mock[i])
		{
			clean_map(mock);
			return (NULL);
		}
		i++;
	}
	mock[i] = NULL;
	return (mock);
}

/*******************************************************************/
/*      flood fill should always start at player posision          */
/*      so we need a find_playe function to detect that            */
/*******************************************************************/
void	find_player(char **map, int *x, int *y)
{
	int	i;
	int	j;

	i = 1;
	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				*x = j;
				*y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

/*******************************************************************/
/*      we will have to check if flood_fill worked so all          */
/*      the indexex in the mocked_map should be 'V'                */
/*      if we see any other letter that will mean there            */
/*      is an unreachable item                                     */
/*******************************************************************/

int	not_flooded(char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if (map[i][j] == 'C' || map[i][j] == 'E')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
