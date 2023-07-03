/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_sanitize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:34:56 by apereira          #+#    #+#             */
/*   Updated: 2023/07/03 12:17:43 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Checks if the command received in ARGV is valid by
// searching for it in the bin folder

char	*check_executable(char *command, char **split_paths)
{
	if (access(command, 0) == 0)
	{
		ft_free(split_paths);
		return (command);
	}
	else
	{
		perror(command);
		return (NULL);
	}
}

char	*check_command(char *command, char **split_paths)
{
	int		i;
	char	*path;
	char	*temp;

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

char	*check_valid_cmd(char *command, char **envp)
{
	char	*cmd;
	char	**split_paths;

	cmd = find_path(envp);
	split_paths = ft_split(cmd, ':');
	if (ft_strcmp(command, "echo") == 0)
	{
		ft_free(split_paths);
		return (command);
	}
	else if (ft_strcmp(command, "cd") == 0)
	{
		ft_free(split_paths);
		return (command);
	}
	else if (ft_strcmp(command, "pwd") == 0)
	{
		ft_free(split_paths);
		return (command);
	}
	else if (ft_strcmp(command, "export") == 0)
	{
		ft_free(split_paths);
		return (command);
	}
	else if (ft_strcmp(command, "unset") == 0)
	{
		ft_free(split_paths);
		return (command);
	}
	else if (ft_strcmp(command, "env") == 0)
	{
		ft_free(split_paths);
		return (command);
	}
	else if (ft_strcmp(command, "exit") == 0)
	{
		ft_free(split_paths);
		return (command);
	}
	if (ft_strchr(command, '/'))
		return (check_executable(command, split_paths));
	else
		return (check_command(command, split_paths));
}
