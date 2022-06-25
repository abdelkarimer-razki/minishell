#include "../../minishell.h"

void	pwd(void)
{
	char	s[100];

	printf("%s\n", getcwd(s, 100));
}
