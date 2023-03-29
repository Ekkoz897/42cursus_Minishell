/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_sanitize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:34:56 by apereira          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/29 16:07:04 by miandrad         ###   ########.fr       */
=======
/*   Updated: 2023/03/29 10:25:34 by apereira         ###   ########.fr       */
>>>>>>> a06c793cc88ada5e4ffb2299a2fed8a83296ba0a
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

<<<<<<< HEAD
/**
 * It counts the number of commands in a string
 * 
 * @param s the string to be split
 * @param c the delimiter
 * 
 * @return The number of commands in the string.
 */
size_t	commands_cpy(char *s)
{
	size_t	i;
	size_t	j;
	char	*cmd;

	i = 0;
	while (s[i])
	{
		while (s[i] == ' ' && s[i] == '	')
			i++;
		j = 0;
		cmd = ft_commands(s);
		while ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
			cmd[j++] = s[i++];
		while (s[i] == ' ' && s[i] == '	')
			i++;
		while (s[i] != '|' && s[i])
		{
			ft_printf("aqui\n");
			while (s[i] == ' ' && s[i] == '	')
				i++;
			while ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
				cmd[j++] = s[i++];
		}
	ft_printf("%s\n" ,cmd);
	}
	return (1);
}

// Allocates for with command size.
char	*ft_commands(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '|' && s[i])
	{
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
			j++;
		i++;	
	}
	ft_printf("%i\n", j);
	return (malloc(sizeof(char) * j + 1));
}

=======
>>>>>>> a06c793cc88ada5e4ffb2299a2fed8a83296ba0a
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
