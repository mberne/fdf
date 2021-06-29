#include "fdf.h"

void	free_split(char **tab, int i)
{
	if (tab)
	{
		while (--i >= 0)
			free(tab[i]);
		free(tab);
	}
}

int	number_of_split(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		while (tab[i])
			i++;
	return (i);
}

int	ft_count(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			i++;
		s++;
	}
	return (i);
}

int	ft_ishexa(char const *s)
{
	if (s)
	{
		while (*s)
		{
			if (!ft_strchr("0123456789abcdefABCDEF", *s))
				return (0);
			s++;
		}
	}
	return (1);
}
