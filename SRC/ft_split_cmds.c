/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:45:56 by apereira          #+#    #+#             */
/*   Updated: 2023/03/30 11:28:22 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * It splits a string into words.
 * 
 */

static char	**free_arr(char **arr, char *s)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	free(s);
	return (NULL);
}

static size_t	words_count(char *s, char c)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (*s)
	{
		i = 1;
		while (*s == c)
			s++;
		while (*s != c && *s)
		{
			if (*s != '|' )
				i = 0;
			if (i != 0)
			{
				j++;
				i = 0;
			}
			s++;
		}
	}
	if (i != 0)
		j++;
	ft_printf("%i\n" , j);
	return (j);
}

static char	*word(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	while (*s == c)
		s++;
	while (s[i] && s[i] != c)
		i++;
	while (1)
	{
		j = i;
		while (s[j] && s[j] == c)
			j++;
		if (s[j] != '-')
			break;
		else
		{
			i = j;
			while (s[i] && s[i] != c)
				i++;
				
		}
	}
	s[i] = '\0';
	return (ft_strdup(s));
}

static char	**worker(char **arr, char *s1, char c, size_t j)
{
	size_t	i;
	char	*str;

	str = s1;
	i = 0;
	while (i < j)
	{
		if (*s1 != c)
		{
			arr[i] = word(s1, c);
			if (!arr[i])
				return (free_arr(arr, s1));
			s1 = s1 + ft_strlen(arr[i]);
			i++;
		}
		s1++;
	}
	arr[i] = NULL;
	free(str);
	return (arr);
}

char	**ft_split_cmds(char const *s, char c)
{
	char	**w_arr;
	char	*s1;
	size_t	j;

	if (!s)
		return (NULL);
	s1 = ft_strdup(s);
	j = words_count(s1, c);
	w_arr = malloc(sizeof(char *) * (j + 1));
	if (!w_arr)
		return (NULL);
	return (worker(w_arr, s1, c, j));
}
