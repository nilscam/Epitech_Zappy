/*
** EPITECH PROJECT, 2018
** utils
** File description:
** utils
*/

#include "utils.hpp"

std::string wchar_to_string(const wchar_t *str)
{
	char *newer = (char *)malloc(100);
	memset(newer, 0, 99);
	wcstombs(newer, str, 99);
	return std::string(newer);
}

const wchar_t *char_to_wchar(const char *str)
{
	const size_t cSize = strlen(str) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, str, cSize);
	return (wc);
}