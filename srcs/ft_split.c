/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyvash <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:33:50 by asyvash           #+#    #+#             */
/*   Updated: 2024/02/01 14:34:21 by asyvash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	int	ft_row_size(char const *s, char c)
{
	int	i;
	int	rows;

	i = 0;
	rows = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] && s[i] != c)
				i++;
			rows++;
		}
	}
	return (rows);
}

static char	*ft_get_word(char *str, char const *s, int pos, int column)
{
	int	j;

	j = 0;
	while (column > 0)
	{
		str[j] = s[pos - column];
		column--;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	**ft_free_error(char **str, int rows)
{
	while (rows > 0)
	{
		free(str[rows]);
		rows--;
	}
	free(str);
	return (0);
}

static char	**ft_make_split(char const *s, char c, char **strs, int rows)
{
	int		i;
	int		row;
	int		column;

	i = 0;
	column = 0;
	row = 0;
	while (row < rows)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			column++;
			i++;
		}
		strs[row] = (char *) malloc(sizeof(char) * (column + 1));
		if (!strs)
			return (ft_free_error(strs, rows));
		ft_get_word(strs[row], s, i, column);
		column = 0;
		row++;
	}
	strs[row] = 0;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		rows;

	if (!s)
		return (NULL);
	rows = ft_row_size(s, c);
	strs = (char **) malloc((rows + 1) * sizeof(char *));
	if (!strs)
		ft_free_error(strs, rows);
	strs = ft_make_split(s, c, strs, rows);
	return (strs);
}
