#include <stdio.h>

int ft_strlen(char *s)
{
	int	i;

	i = 0;
    if (s == NULL)
        return (0);
	while (s[i])
		i++;
	return (i);
}

int main()
{
    char *c;

    c = NULL;
    printf("%d\n", ft_strlen(c));
}