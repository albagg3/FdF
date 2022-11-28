/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:29:30 by albagarc          #+#    #+#             */
/*   Updated: 2022/11/27 18:30:34 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/defines.h"
#include "../inc/get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include "../lib/libft_src/libft.h"
#include "../lib/minilibx_macos/mlx.h"
#include "../inc/utils.h"

//Contamos los elementos de cada linea, con este dato podremos ir comparandolo
// y sabiendo si todas las lineas tienen el mismo numero de elementos para que
//pueda ser un mapa valido.

int	count_elems_line(char **split)
{
	int	i;

	i = 0;
	while (split[i] && split[i][0] != '\n')
		i++;
	return (i);
}

//Con esta funcion vamos recorriendo el mapa y guardamos los maximos y 
//comprobamos si el mapa es valido. para poder contar los elementos hacemos 
//el split y nos quita los espacios y tenemos cada valor en un array. 
int	valid_map(char	*file_name, t_map *map)
{
	int		fd;
	char	*line;
	char	**splitted;
	int		max_x;

	map->total_size = 0;
	map->limits.coord[X] = 0;
	map->limits.coord[Y] = 0;
	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		splitted = ft_split(line, ' ');
		max_x = count_elems_line(splitted);
		if (map->limits.coord[X] == 0)
			map->limits.coord[X] = max_x;
		if (map->limits.coord[X] != max_x)
			return (0);
		line = get_next_line(fd);
		map->total_size += max_x;
		map->limits.coord[Y]++;
	}
	close(fd);
	return (1);
}

void	ft_load_color(t_map *map, char *line)
{
	char	**color;

	if (ft_strchr(line, ',') != 0)
	{
		color = ft_split(line, ',');
		printf("entra: %s ",color[1]);
		map->points[map->len].color = (long)strtol(color[1] + 2, NULL, 16);
		printf("sale: %x\n ", map->points[map->len].color);
	//dbl_free aitor
	}
	else
		map->points[map->len].color = 0xFFFF00;
}

//Funcion que me guarde los valores de los puntos en arrays
void	save_map_points(t_map *map, int line_number, char *line)
{
	int		i;
	char	**splitted;

	i = 0;
	splitted = ft_split(line, ' ');
	while (splitted[i] && splitted[i][0] != '\n')
	{
		map->points[map->len].coord[X] = i - map->limits.coord[X] / 2;
		map->points[map->len].coord[Y] = line_number - map->limits.coord[Y] / 2;
		map->points[map->len].coord[Z] = ft_atoi(splitted[i]);
		ft_load_color(map, splitted[i]);
		i++;
		map->len++;
	}
}

//funcion que junto con la anterior me guarda en un array todos 
//los valores de los puntos.

int	load_map(char *file_name, t_map *map)
{
	int		line_number;
	int		fd;
	char	*line;

	line_number = 0;
	map_init(map);
	valid_map(file_name, map);
	map->points = ft_calloc (map->total_size, sizeof(t_point));
	if (map->points == NULL)
		return (0);
	fd = open(file_name, O_RDONLY);
	if (fd < 2)
		return (0);
	line = get_next_line(fd);
	map->len = 0;
	while (line != NULL)
	{
		save_map_points(map, line_number, line);
		line_number++;
		line = get_next_line(fd);
	}
	return (1);
}

int	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WINX || y >= WINY || x < 0 || y < 0)
		return (-1);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (0);
}

void	draw_points(t_all *all, t_point *copy_points)
{
	int	i;

	i = 0;
	while (i < all->map.total_size)
	{
		my_mlx_pixel_put(&all->data, copy_points[i].coord[X] + WINX / 2, \
			copy_points[i].coord[Y] + WINY / 2, 0xff0000);
		i++;
	}
}
