#include "../cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_error(int error_code)
{
	if (error_code == MALLOC)
		printf("Error\n\U0001f4a9 Malloc failure \U0001f4a9\n");
	exit(0);
}
