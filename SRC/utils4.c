/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:53:05 by apereira          #+#    #+#             */
/*   Updated: 2023/11/14 17:21:38 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_delimiter(char c, char *delimiters)
{
	while (*delimiters)
	{
		if (c == *delimiters)
			return (1);
		delimiters++;
	}
	return (0);
}

char	*remove_quotes_from_string(char *str)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = (char *)malloc((strlen(str) + 1) * sizeof(char));
	ft_remove_quotes_helper(str, new_str, &i);
	new_str[i] = '\0';
	return (new_str);
}

void	remove_quotes_from_array(char **arr)
{
	int		i;
	char	*new_str;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		new_str = remove_quotes_from_string(arr[i]);
		free(arr[i]);
		arr[i] = new_str;
		i++;
	}
}

char	*ft_strjoin_char(char *str1, char c)
{
	char	*new_str;
	int		i;

	if (!str1)
	{
		new_str = malloc(sizeof(char) * 2);
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}
	new_str = malloc(sizeof(char) * (ft_strlen(str1) + 2));
	i = 0;
	while (str1[i])
	{
		new_str[i] = str1[i];
		i++;
	}
	new_str[i] = c;
	i++;
	new_str[i] = '\0';
	return (new_str);
}

char	*get_value_for_expand(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	if (!str)
		return ("");
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	i++;
	j = i;
	while (str[j])
		j++;
	value = malloc(sizeof(char) * (j - i + 1));
	if (!value)
		return ("");
	ft_strlcpy(value, str + i, j - i + 1);
	return (value);
}
