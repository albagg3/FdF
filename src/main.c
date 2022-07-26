/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:27:23 by albagarc          #+#    #+#             */
/*   Updated: 2022/11/30 18:26:08 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "../lib/minilibx_macos/mlx.h"
#include "../inc/keycode_hook.h"
#include "../inc/utils.h"
#include "../inc/defines.h"
#include "../inc/errors.h"

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc != 2)
		terminate (ERR_ARGS);
	load_map(argv[1], &all.map);
	all.vars.mlx = mlx_init();
	all.vars.win = mlx_new_window(all.vars.mlx, 1920, 1080, "Fdf");
	all.data.img = mlx_new_image(all.vars.mlx, 1920, 1080);
	all.data.addr = mlx_get_data_addr(all.data.img, &all.data.bits_per_pixel, \
		&all.data.line_length, &all.data.endian);
	mlx_hook(all.vars.win, 2, 0, key_press, &all.vars);
	mlx_hook(all.vars.win, 17, 0, ft_destroy_window, &all.vars);
	mlx_hook(all.vars.win, 4, 0, ft_mouse_down, &all.vars);
	mlx_hook(all.vars.win, 5, 0, ft_mouse_up, &all.vars);
	mlx_hook(all.vars.win, 6, 0, ft_mouse_move, &all.vars);
	mlx_loop(all.vars.mlx);
	return (0);
}
