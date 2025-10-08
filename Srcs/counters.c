/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauafth <asauafth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 03:49:08 by asauafth          #+#    #+#             */
/*   Updated: 2025/10/08 09:56:58 by asauafth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/***************************************************************/
/*   also we need to check how many player && exits are there  */
/*   cause they only supposed to be == 1                       */
/***************************************************************/

void	check_map_tools(char **map, int rows, int columns, int *p_ctr, int *e_ctr)
{
	int	i;
	int	j;

	i = 1;
	while (i < (rows - 1))
	{
		j = 1;
		while (j < columns - 1)
		{
			if (map[i][j] == 'P')
				(*p_ctr)++;
			else if (map[i][j] == 'E')
				(*e_ctr)++;
			j++;
		}
		i++;
	}
}
/***********************************************************/
/*   we need to count the collectibles to make sure that   */
/*   they are > 1 and down the road we need to check       */
/*   if we collected all of them                           */
/***********************************************************/

int	count_collectibles(char **map)
{
	int	i;
	int	j;
	int rows;
	int columns;
	int	counter;

	i = 1;
	counter = 0;
	map_measurements(map, &rows, &columns);
	while (i < rows - 1)
	{
		j = 1;
		while (j < columns - 1)
		{
			if (map[i][j] == 'C')
				counter++;
			j++;
		}
		i++;
	}
	return (counter);
}
int	ft_strlen_so_long(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
