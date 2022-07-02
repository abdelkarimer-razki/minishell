#include "../minishell.h"

void	dup_and_close(int **fd, int i, int ioo)
{
	if (ioo == 1)
	{
		dup2(fd[i][1], STDOUT_FILENO);
		close(fd[i][1]);
	}
	else if (ioo == 0)
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		close(fd[i - 1][0]);
	}
}
