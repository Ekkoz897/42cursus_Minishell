/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:45:56 by apereira          #+#    #+#             */
/*   Updated: 2023/04/03 11:06:52 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * It splits a string into words.
 * 
 */

// static char	**free_arr(char **arr, char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// 	free(s);
// 	return (NULL);
// }

int	get_token_length(const char *str, const char *delimiters)
{
	int	length;

	length = 0;
	while (str[length] && !ft_strchr(delimiters, str[length]))
		length++;
	return (length);
}

const char	*get_next_token(const char *str, const char *delimiters)
{
	while (*str && ft_strchr(delimiters, *str))
	str++;
	if (*str)
		return (str);
	else
		return (NULL);
}

char	**ft_split_commands(const char *str, const char *delimiters)
{
	int			num_words;
	char		**words;
	const char	*token_start;
	int			token_length;
	int			i;

	num_words = count_words(str, delimiters);
	words = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	i = 0;
	token_start = get_next_token(str, delimiters);
	while (token_start)
	{
		token_length = get_token_length(token_start, delimiters);
		words[i] = ft_strndup(token_start, token_length);
		if (!words[i++])
		{
			ft_free(words);
			return (NULL);
		}
		token_start = get_next_token(token_start + token_length, delimiters);
	}
	words[num_words] = NULL;
	return (words);
}
