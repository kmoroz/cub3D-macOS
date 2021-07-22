#include "../cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void	map_error(int error_code)
{
	if (error_code == PLAYER_INVALID)
		printf("Error\n\U0001f4a9 Invalid player \U0001f4a9\n");
	if (error_code == MAP_INVALID)
		printf("Error\n\U0001f4a9 Invalid map \U0001f4a9\n");
	if (error_code == MAP_ON_TOP)
		printf("Error\n\U0001f4a9 Map on top OR wrong number of identifiers \U0001f4a9\n");
}

void	ft_error(int error_code)
{
	if (error_code == MALLOC)
		printf("Error\n\U0001f4a9 Malloc failure \U0001f4a9\n");
	if (error_code == IDENTIFIER_ILLEGAL)
		printf("Error\n\U0001f4a9 Wrong type identifier \U0001f4a9\n");
	if (error_code == WRONG_RES)
		printf("Error\n\U0001f4a9 Invalid resolution value \U0001f4a9\n");
	if (error_code == FILE_MISSING)
		printf("Error\n\U0001f4a9 Texture file missing \U0001f4a9\n");
	if (error_code == RGB_INVALID)
		printf("Error\n\U0001f4a9 Invalid RGB value \U0001f4a9\n");
	if (error_code == ARG_COUNT_WRONG)
		printf("Error\n\U0001f4a9 Wrong number of arguments \U0001f4a9\n");
	if (error_code == EXTENSION_INVALID)
		printf("Error\n\U0001f4a9 Invalid file extension \U0001f4a9\n");
	if (error_code == ZERO_RES)
		printf("Error\n\U0001f4a9 Resolution cannot be zero \U0001f4a9\n");
	if (error_code == RGB_EXCEEDED)
		printf("Error\n\U0001f4a9 Max RGB value exceeded \U0001f4a9\n");
	if (error_code == ZERO_TEXTURE)
		printf("Error\n\U0001f4a9 Texture path missing \U0001f4a9\n");
	if (error_code == IDENTIFIERS)
		printf("Error\n\U0001f4a9 Incorrect number of identifiers \U0001f4a9\n");
	map_error(error_code);
	exit(1);
}
