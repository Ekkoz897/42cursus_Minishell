/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:05:24 by apereira          #+#    #+#             */
/*   Updated: 2023/05/02 15:34:13 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_token_length_no_redirection(char *str, char *delimiters)
{
	int	length;

	length = 0;
	while (str[length] && !ft_strchr(delimiters, str[length]))
	{
	length++;
	}
	return (length);
}

char	*get_next_token_no_redirection(char *str,
		char *delimiters)
{
	while (*str && *str == ' ')
		str++;
	if (*str == '<' || *str == '>')
	{
		str++;
		while (*str && ft_strchr(delimiters, *str))
			str++;
		while (*str && !ft_strchr(delimiters, *str))
			str++;
		while (*str && *str == ' ')
			str++;
	}
	if (*str)
		return (str);
	else
		return (NULL);
}

int	count_words_no_redirection(char *str, char *delimiters)
{
	int		count;
	int		token_length;
	char	*token_start;

	count = 0;
	token_start = get_next_token_no_redirection(str, delimiters);
	while (token_start)
	{
	count++;
	token_length = get_token_length_no_redirection(token_start, delimiters);
	token_start = get_next_token_no_redirection(token_start + token_length,
				delimiters);
	}
	return (count);
}

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

// Para printar os tokens individuais, adionar na linha 114:
// i = 0;
// 	while (tokens[i])
// 	{
// 		ft_printf("token [%i] = %s\n", i, tokens[i]);
// 		i++;
// 	}
char	**ft_split_commands_no_redirection(char *str, char *delimiters)
{
	char	**tokens;
	int		num_words;
	char	*token_start;
	int		token_length;
	int		i;

	num_words = count_words_no_redirection(str, delimiters);
	tokens = malloc((num_words + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	token_start = (char *)str;
	i = 0;
	while (token_start)
	{
		token_start = get_next_token_no_redirection(token_start, delimiters);
		if (token_start && *token_start != '>' && *token_start != '<')
		{
			token_length = get_token_length(token_start, delimiters);
			tokens[i++] = ft_strndup(token_start, token_length);
			token_start += token_length;
		}
	}
	tokens[i] = NULL;
	return (tokens);
}
