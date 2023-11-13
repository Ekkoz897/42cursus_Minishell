/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miandrad <miandrad@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:27:54 by apereira          #+#    #+#             */
/*   Updated: 2023/11/13 12:54:27 by miandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*str;

	if (!s1 && !s2 && !s3)
		return (NULL);
	else if (!s1 && (s2 && s3))
		str = ft_strjoin(s2, s3);
	else if (!s2 && (s1 && s3))
		str = ft_strjoin(s1, s3);
	else if (!s3 && (s1 && s2))
		str = ft_strjoin(s1, s2);
	else if (s1 && !s2 && !s3)
		str = ft_strdup(s1);
	else if (s2 && !s1 && !s3)
		str = ft_strdup(s2);
	else if (s3 && !s1 && !s2)
		str = ft_strdup(s3);
	else
	{
		str = NULL;
		ft_strjoin_three_help(s1, s2, s3, str);
	}
	return (str);
}

void	add_env_var(t_vars *vars, char *name, char *value)
{
	int		i;
	char	**new_environ;
	char	*new_env_var;

	new_environ = malloc((vars->num_env_vars + 2) * sizeof(char *));
	if (!new_environ)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < vars->num_env_vars)
	{
		new_environ[i] = vars->my_environ[i];
		i++;
	}
	new_env_var = ft_strjoin_three(name, "=", value);
	new_environ[i] = new_env_var;
	new_environ[i + 1] = NULL;
	free(vars->my_environ);
	vars->my_environ = new_environ;
	vars->num_env_vars++;
}

void	modify_env_var(t_vars *vars, char *name, char *new_value)
{
	int		i;
	int		name_len;
	char	*new_env_var;

	name_len = ft_strlen(name);
	i = 0;
	while (vars->my_environ[i])
	{
		if (ft_strncmp(vars->my_environ[i], name, name_len) == 0 \
			&& vars->my_environ[i][name_len] == '=')
		{
			free(vars->my_environ[i]);
			new_env_var = ft_strjoin_three(name, "=", new_value);
			vars->my_environ[i] = new_env_var;
			return ;
		}
		i++;
	}
	add_env_var(vars, name, new_value);
}

char	*get_env_var(t_vars *vars, char *name)
{
	int		i;
	int		name_len;

	name_len = ft_strlen(name);
	i = 0;
	while (vars->my_environ[i])
	{
		if (ft_strncmp(vars->my_environ[i], name, name_len) == 0 \
			&& vars->my_environ[i][name_len] == '=')
			return (vars->my_environ[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

// static to stay within 25 lines without spliting such a simple
// function in two.
void	copy_environ(char **environ, t_vars *vars)
{
	int		i;
	int		j;

	i = 0;
	while (environ[i] != NULL)
		i++;
	vars->num_env_vars = i;
	vars->my_environ = malloc(sizeof(char *) * (i + 1));
	if (!vars->my_environ)
		return ;
	i = 0;
	while (environ[i] != NULL)
	{
		vars->my_environ[i] = ft_strdup(environ[i]);
		if (vars->my_environ[i] == NULL)
		{
			j = 0;
			while (j < i)
				free(vars->my_environ[j++]);
			free(vars->my_environ);
			return ;
		}
		i++;
	}
	vars->my_environ[i] = NULL;
}
