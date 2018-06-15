/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** str_to_tab.h
*/

#ifndef str_to_tab_HPP
#define str_to_tab_HPP

# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

/* str_to_tab.c */
char	**str_to_tab(char *str, char *delims);
void	free_tab(char **tab);

#endif // !str_to_tab_HPP
