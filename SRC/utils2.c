/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:05:24 by apereira          #+#    #+#             */
/*   Updated: 2023/11/09 16:14:15 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_token_length_no_redirection(char *token_start, char *delimiters)
{
	int		length;
	char	current_quote;

	length = 0;
	current_quote = '\0';
	ft_get_token_l_noredirection_helper(&length, token_start, delimiters, \
		current_quote);
	return (length);
}

char	*get_next_token_no_redirection(char *str, char *delimiters)
{
	int		in_quotes;
	char	current_quote;

	in_quotes = 0;
	current_quote = '\0';
	while (*str)
	{
		if (in_quotes == 0 && ft_strchr(delimiters, *str))
		{
			if (*str == > || *str == <)
			{
				funcao_nova();
			}
			str++;
		}
		else
			break ;
		ft_get_next_token_noredirection_helper(*str, &in_quotes, \
			&current_quote);
	}
	if (*str != '\0')
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

/**
 * The function "process_token" takes in an array of tokens, a pointer to the
 * start of a token, a string of delimiters, and a pointer to an integer. It 
 * extracts the next token from the token start, checks if it is not a
 * redirection symbol, gets the length of the token, duplicates the token
 * and stores it in the tokens array, updates the token start pointer,
 * and increments the integer pointer.
 */
void	process_token(char **tokens, char **token_start,
		char *delimiters, int *i)
{
	int	token_length;

	*token_start = get_next_token_no_redirection(*token_start, delimiters);
	if (*token_start && **token_start != '>' && **token_start != '<')
	{
		token_length = get_token_length(*token_start, delimiters);
		tokens[*i] = ft_strndup(*token_start, token_length);
		*token_start += token_length;
		(*i)++;
	}
}

/**
 * Splits a string into tokens based on a set of delimiters, excluding any
 * tokens that contain redirection symbols.
 * 
 * @param str - string containing the input commands.
 * @param delimiters - string containing the characters used as
 * delimiters to split the input string.
 * 
 * @return the split commands as an array of strings.
 */
char	**ft_split_commands_no_redirection(char *str, char *delimiters)
{
	char	**tokens;
	int		num_words;
	char	*token_start;
	int		token_length;
	int		i;

	if (str == NULL)
		return (NULL);
	num_words = count_words_no_redirection(str, delimiters);
	tokens = malloc((num_words + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	token_start = (char *)get_next_token_no_redirection(str, delimiters);
	i = 0;
	while (token_start)
	{
		ft_printf("%s\n", token_start);
		token_length = get_token_length_no_redirection(token_start, delimiters);
		tokens[i++] = ft_strndup(token_start, token_length);
		token_start += token_length;
		token_start = get_next_token_no_redirection(token_start, delimiters);
	}
	tokens[i] = NULL;
	i = 0;
	while (tokens[i])
	{
		ft_printf("tokens : %s\n", tokens[i]);
		i++;
	}
	return (tokens);
}
