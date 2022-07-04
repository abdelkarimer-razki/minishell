/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboulhan <bboulhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:09:15 by bboulhan          #+#    #+#             */
/*   Updated: 2022/07/04 18:18:44 by bboulhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char	*add_char(char *str, char c)
{
	char	*s;
	int		j;

	j = -1;
	s = calloc(strlen(str) + 2, 1);
	if (!s)
		return (0);
	while (str[++j])
		s[j] = str[j];
	if (j == -1)
		j = 0;
	s[j++] = c;
	s[j] = 0;
	free(str);
	return (s);
}

int main(int ac, char **av)
{
    char    *s;
    int     i = -1;
    
    if (ac == 2)
    {
        s = strdup("leaks ");
        while (av[1][++i])
            s = add_char(s, av[1][i]);
        while (1)
        {
            system(s);
            sleep(1);
            usleep(750000);
            system("clear");
        }
    }
    else
        write(2, "error\n", 6);
    free(s);
    return (0);
}