#include "minishell.h"
int main()
{
	char *s;
	int *j;
	s = ft_error(3, NULL, NULL, NULL);
	j = ft_error(4, NULL, NULL, 1);
	printf("%s\t%d\n", s, j);
}


void	handler(int sig, siginfo_t *siginfo, void *content)
{
	static int	x = 8;
	static int	n = 0;
	static int	rs = 0;

	(void)content;
	if (x == 0 && n == 8)
	{	
		ft_putchar(rs);
		rs = 0;
		x = 8;
		n = 0;
	}
	if (sig == SIGUSR1)
		rs = rs + ft_power(2, n);
	if (x == 8 && n == 0 && rs <= 1)
		g_pid = siginfo->si_pid;
	check_signal(siginfo->si_pid, x, rs, n);
	x--;
	n++;
}

int	main(void)
{
	struct sigaction	red;

	red.sa_sigaction = &handler;
	red.sa_flags = SA_SIGINFO;
	ft_putstr("the pid is : ");
	ft_putnbr (getpid());
	ft_putchar ('\n');
	while (1)
	{
		sigaction(SIGUSR1, &red, NULL);
		sigaction(SIGUSR2, &red, NULL);
		pause();
	}
	return (0);
}