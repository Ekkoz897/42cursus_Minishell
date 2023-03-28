/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_sanitize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:34:56 by apereira          #+#    #+#             */
/*   Updated: 2023/03/28 17:12:51 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	commands_count(char *s)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (*s)
	{
		if (*s == ' ' || *s == '	')
			i++;
		else if (*s != ' ' && *s != '	' && i != 0 && *s != '-')
		{
			words++;
			i = 0;
		}
		s++;
	}
	if (i != 0)
		words++;
	return (words);
}

// Splits into sub arrays  seperate commands.
char	**ft_commands(char *argv)
{
	char	**commands;
	int		i;

	i = 0;
	commands = malloc(sizeof(char *));
	while (i < commands_count(argv))
	{
		commands[i] = malloc(sizeof(char *));
		i++;
	}
}

// Finds the PATH string in the "envp" text
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);
}

// Checks if the command received in ARGV is valid by
// searching for it in the bin folder
char	*check_valid_cmd(char *command, char **envp)
{
	int		i;
	char	**split_paths;
	char	*path;
	char	*temp;
	char	*cmd;

	cmd = find_path(envp);
	split_paths = ft_split(cmd, ':');
	i = 0;
	while (split_paths[i])
	{
		temp = ft_strjoin(split_paths[i], "/");
		path = ft_strjoin(temp, command);
		free (temp);
		if (access(path, 0) == 0)
		{
			ft_free(split_paths);
			return (path);
		}
		free (path);
		i++;
	}
	ft_free (split_paths);
	ft_printf("Command not found: %s\n", command);
	return (NULL);
}
