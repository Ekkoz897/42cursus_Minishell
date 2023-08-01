/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:05:24 by apereira          #+#    #+#             */
/*   Updated: 2023/08/01 13:43:20 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_token_length_no_redirection(char *token_start, char *delimiters)
{
	int		length;
	int		in_quotes;
	char	current_quote;

	length = 0;
	in_quotes = 0;
	current_quote = '\0';
	while (*token_start)
	{
		if (in_quotes == 0 && ft_strchr(delimiters, *token_start))
			break ;
		if (*token_start == '\'' || *token_start == '\"')
		{
			if (in_quotes == 0 || current_quote == *token_start)
			{
				in_quotes = !in_quotes;
				if (in_quotes)
					current_quote = *token_start;
				else
					current_quote = '\0';
			}
		}
		token_start++;
		length++;
	}
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
			str++;
		else
			break ;
		if (*str == '\'' || *str == '\"')
		{
			if (in_quotes == 0 || current_quote == *str)
			{
				in_quotes = !in_quotes;
				if (in_quotes)
					current_quote = *str;
				else
					current_quote = '\0';
			}
		}
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
		token_length = get_token_length_no_redirection(token_start, delimiters);
		tokens[i++] = ft_strndup(token_start, token_length);
		token_start += token_length;
		token_start = get_next_token_no_redirection(token_start, delimiters);
	}
	tokens[i] = NULL;
	return (tokens);
}
