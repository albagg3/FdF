/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albagarc <albagarc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 09:04:04 by albagarc          #+#    #+#             */
/*   Updated: 2022/11/27 18:39:21 by albagarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "../inc/defines.h"
#include <math.h>

//Funcion que multiplica 2 matrices una de 3x3(matriz de transformacion) y otra
//de 3x1(punto del mapa). Nos devuelve el punto ya transformado.
//t_point result : punto transformado
//contador i: para recorrer las rows de la matriz de 3x3
//contador k: recorre las col de la matriz de 3x3 y las row de la matriz de 3x1

t_point	mat_mul(float matrix [3][3], t_point point)
{
	t_point	result;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (i < 3)
	{
		result.coord[i] = 0;
		k = 0;
		while (k < 3)
		{
			result.coord[i] += matrix[i][k] * point.coord[k];
			k++;
		}
		i++;
	}
	result.color = point.color;
	return (result);
}

//Funcion que nos inicia una matriz e 3x3 con todo 0 para rellenar solo 
//los valores que necesitamos de la matriz de rotacion.

void	matrix_zero(float matrix[3][3])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			matrix[i][j] = 0;
			j++;
		}
		i++;
	}
}

//Funcion que rota los puntos en el eje X

void	rotation_x(int len, t_point *points, t_point *projected, int ang)
{
	float	rotation_matrix[3][3];
	float	rad;
	int		i;

	i = 0;
	rad = ang * M_PI / 180;
	matrix_zero (rotation_matrix);
	rotation_matrix[0][0] = 1;
	rotation_matrix[1][1] = cos(rad);
	rotation_matrix[1][2] = -sin(rad);
	rotation_matrix[2][1] = sin(rad);
	rotation_matrix[2][2] = cos(rad);
	while (i < len)
	{
		projected[i] = mat_mul(rotation_matrix, points[i]);
		i++;
	}
}

//Funcion que rota los puntos en el eje Y

void	rotation_y(int len, t_point *points, t_point *projected, int ang)
{
	float	rotation_matrix[3][3];
	float	rad;
	int		i;

	i = 0;
	rad = ang * M_PI / 180;
	matrix_zero (rotation_matrix);
	rotation_matrix[0][0] = cos(rad);
	rotation_matrix[0][2] = sin(rad);
	rotation_matrix[1][1] = 1;
	rotation_matrix[2][0] = -sin(rad);
	rotation_matrix[2][2] = cos(rad);
	while (i < len)
	{
		projected[i] = mat_mul(rotation_matrix, points[i]);
		i++;
	}
}

//Funcion que rota los puntos en el eje Z

void	rotation_z(int len, t_point *points, t_point *projected, int ang)
{
	float	rotation_matrix[3][3];
	float	rad;
	int		i;

	i = 0;
	rad = ang * M_PI / 180;
	matrix_zero (rotation_matrix);
	rotation_matrix[0][0] = cos(rad);
	rotation_matrix[0][1] = -sin(rad);
	rotation_matrix[1][0] = sin(rad);
	rotation_matrix[1][1] = cos(rad);
	rotation_matrix[2][2] = 1;
	while (i < len)
	{
		projected[i] = mat_mul(rotation_matrix, points[i]);
		i++;
	}
}
