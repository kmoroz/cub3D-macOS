#include "../cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_error(int error_code)
{
	if (error_code == MALLOC)
		printf("Error\n\U0001f4a9 Malloc failure \U0001f4a9\n");
	if (error_code == IDENTIFIER_ILLEGAL)
		printf("Error\n\U0001f4a9 Wrong type identifier \U0001f4a9\n");
	if (error_code == WRONG_RES)
	{
		printf("Error\n\U0001f4a9 Please check ");
		printf("the resolution values provided. \U0001f4a9\n");
	}
	if (error_code == MAP_ON_TOP)
	{
		printf("Error\n\U0001f4a9 Map is on top OR incorrect number of type identifiers \U0001f4a9\n");
	}
	if (error_code == FILE_MISSING)
		printf("Error\n\U0001f4a9 Texture file missing \U0001f4a9\n");
	exit(0);
}
