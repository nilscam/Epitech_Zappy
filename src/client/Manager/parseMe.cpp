/*
** EPITECH PROJECT, 2018
** parseMe
** File description:
** parseMe
*/

#include "Manager.hpp"

int	pars_opt(char *str, const char *opt, int j)
{
    int	i = -1;

    if (opt[0] == 0 && ((0 <= str[j] && str[j] <= 47) ||
                        (58 <= str[j] && str[j] <= 64) ||
                        (91 <= str[j] && str[j] <= 96) ||
                        (123 <= str[j] && str[j] <= 126)))
        return (0);
    while (opt[++i])
        if (str[j] == opt[i])
            return (0);
    return (-1);
}

void	go_end(int *count, int *i, char *str, const char *opt)
{
    ++(*count);
    while (str[++(*i)] && (pars_opt(str, opt, *i)) == 0);
    *i = (str[*i] == 0 ? (*i) -1 : (*i));
}

int	malloc_tab(char *str, const char *opt)
{
    int	i = -1;
    int	count = 0;

    while (str[++i]) {
        if ((pars_opt(str, opt, i)) == 0)
            go_end(&count, &i, str, opt);
    }
    return (count + 2);
}

char	**Manager::parseMe(char *string, const char *opt)
{
    int	i = -1;
    int	j = -1;
    char	*str;
    int	len;
    char	**tab;

    if (string == NULL)
        return (NULL);
    str = strdup(string);
    len = strlen(str);
    tab = (char **)malloc(sizeof(char*) * malloc_tab(str, opt));
    while (str[++i])
        if ((pars_opt(str, opt, i)) == 0)
            str[i] = 0;
    i = -1;
    while (++i < len)
        if ((i == 0 && str[i] != 0) ||
            (str[i] != 0 && str[i - 1] == 0))
            tab[++j] = &str[i];
    tab[++j] = NULL;
    return (tab);
}