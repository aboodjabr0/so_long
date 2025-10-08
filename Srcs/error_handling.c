/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asauafth <asauafth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:43:06 by asauafth          #+#    #+#             */
/*   Updated: 2025/10/05 11:54:27 by asauafth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*******************************************************************/
/*  this file is responable to check the number of arguments,      */
/*  if the file sent by the user is a valid file                   */
/*  by checking if the file exist and the extension and the content*/
/*******************************************************************/

#include "so_long.h"

int	invalid_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("file doesn't exist !!");
		return (1);
	}
	close(fd);
	return (0);
}

int	check_extension(char *file)
{
	int	file_name_len;

	file_name_len = ft_strlen_so_long(file);
	if (file_name_len < 5 || ft_strncmp(file + file_name_len - 4, ".ber", 4))
	{
		ft_printf("File doesn't end with .ber");
		return (1);
	}
	return (0);
}

int	empty_file_check(char *file)
{
	char	buff[1];
	int		fd;
	int		bytes;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Opening file failed");
		return (1);
	}
	bytes = read(fd, buff, 1);
	close(fd);
	if (bytes < 0)
	{
		ft_printf("reading file Error");
		return (1);
	}
	if (bytes == 0)
	{
		ft_printf("The file is empty");
		return (1);
	}
	return (0);
}

void	validate_file(int argc, char *argv)
{
	if (argc < 2)
	{
		ft_printf("Error\nUsage: %s <map.ber>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (invalid_file(argv) || check_extension(argv) || empty_file_check(argv))
	{
		exit(EXIT_FAILURE);
	}
}
