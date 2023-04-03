/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 08:04:34 by apereira          #+#    #+#             */
/*   Updated: 2023/04/03 11:01:33 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Finds the PATH string in the "envp" text
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);
}

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free (array);
}

// ft_lst_addback but with char ** and diff struct
t_cmds	*create_new_node(char **command)
{
	t_cmds	*new_node;

	new_node = (t_cmds *)malloc(sizeof(t_cmds));
	if (!new_node)
		return (NULL);
	new_node->content = (void *)command;
	new_node->next = NULL;
	return (new_node);
}

// ft_lst_addnew but with char ** and diff struct
t_cmds	*link_new_node(t_cmds *current, char **commands)
{
	if (!current)
		return (create_new_node(commands));
	current->next = create_new_node(commands);
	return (current->next);
}

int	count_words(const char *str, const char *delimiters)
{
	int			count;
	int			token_length;
	const char	*token_start;

	count = 0;
	token_start = get_next_token(str, delimiters);
	while (token_start)
	{
		count++;
		token_length = get_token_length(token_start, delimiters);
		token_start = get_next_token(token_start + token_length, delimiters);
	}
	return (count);
}