#include "stdio.h"

int main(int arc, char **argv)
{
	int	i;

	i = 0;
	while (++i < arc)
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
	}
}