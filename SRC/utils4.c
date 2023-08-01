/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 12:53:05 by apereira          #+#    #+#             */
/*   Updated: 2023/08/01 13:42:13 by apereira         ###   ########.fr       */
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

char	*remove_quotes_from_string(const char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = (char *)malloc((strlen(str) + 1) * sizeof(char));
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
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
