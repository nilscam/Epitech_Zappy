/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** math_utils.c
*/

#include "math_utils.h"

double	dmod(double a, double b)
{
	return b == 0 ? 0 : a - b * floor(a / b);
}

double	to_valid_angle(double d)
{
	d = dmod(d, 360);
	while (d < 0)
		d += 360.0;
	return d;
}

int	randome_between(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
