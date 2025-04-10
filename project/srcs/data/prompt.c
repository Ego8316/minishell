/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:33:19 by ego               #+#    #+#             */
/*   Updated: 2025/04/10 18:59:38 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Tries and get the hostname from the file /etc/hostname.
 * Reads it with get_next_line. If the file cannot be found,
 * hostname is set to "42" by default. Also adds color to it.
 * 
 * @return Allocated copy of the hostname, NULL if allocation fails.
 */
static char	*get_hostname(void)
{
	char	*hostname;
	char	*tmp;
	int		fd;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return (join_strs(COLOR_BLUE, "42", COLOR_RESET));
	hostname = get_next_line(fd);
	tmp = ft_strtrim(hostname, "\n");
	free_str(&hostname);
	close(fd);
	if (!tmp)
		return (NULL);
	hostname = join_strs(COLOR_BLUE, tmp, COLOR_RESET);
	free_str(&tmp);
	return (hostname);
}

/**
 * @brief Tries and get the user from the environment.
 * If not found or empty, the user is to "user" by default.
 * Also adds color to it.
 * 
 * @return Allocated copy of the user, NULL if allocation fails.
 */
static char	*get_user(void)
{
	char	*user;

	user = getenv("USER");
	if (!user || !*user)
		return (join_strs(COLOR_GREEN, "user", COLOR_RESET));
	else
		return (join_strs(COLOR_GREEN, user, COLOR_RESET));
}

/**
 * @brief Builds the full prefix of the form
 * "user @ hostname :" with color after.
 * 
 * @return Allocated prefix, NULL if allocation fails. 
 */
char	*get_prefix(void)
{
	char	*user;
	char	*hostname;
	char	*tmp;
	char	*prefix;

	user = get_user();
	if (!user)
		return (NULL);
	hostname = get_hostname();
	if (!hostname)
		return (free(user), NULL);
	tmp = join_strs(user, "@", hostname);
	free_str(&user);
	free_str(&hostname);
	if (!tmp)
		return (NULL);
	prefix = join_strs(tmp, ":", COLOR_RED);
	free_str(&tmp);
	return (prefix);
}

/**
 * @brief Adds the current working directory to the prompt.
 * First gets the value of PWD in the variables. If not found,
 * data structure has a backup with the working directory at
 * all time. Then, if home is set, will search in the working
 * directory if value of HOME can be substituted in PWD. If
 * so, replace it by a tilde. If not, simply puts the found
 * working directory.
 * 
 * @param data Pointer to the data structure.
 * @param prompt Prompt buffer.
 * @param prefix_len Length of the prefix.
 * 
 * @return The length of whatever the function will attempt to copy
 * into the prompt.
 */
int	add_pwd_to_prompt(t_data *data, char *prompt, int prefix_len)
{
	t_var	*home;
	int		dstsize;
	int		home_len;
	t_var	*pwd;
	char	*pwd_value;

	pwd = var_get(&data->vars, "PWD");
	if (!pwd)
		pwd_value = data->pwd;
	else
		pwd_value = pwd->value;
	prompt += prefix_len;
	home = var_get(&data->vars, "HOME");
	dstsize = PROMPT_LEN - prefix_len - SUFFIX_LEN;
	if (!home || !*home->value)
		return (ft_strlcpy(prompt, pwd_value, dstsize));
	home_len = ft_strlen(home->value);
	if (ft_strncmp(pwd_value, home->value, home_len + 1) == '/')
	{
		prompt[0] = '~';
		return (ft_strlcpy(prompt + 1, pwd_value + home_len, dstsize - 1));
	}
	return (ft_strlcpy(prompt, pwd_value, dstsize));
}

/**
 * @brief Builds the full prompt.
 * 
 * @param data Pointer to the data structure.
 * @param mode Function's mode to be called with,
 * 0 to build it, 1 to just get it and 2 to update it.
 */
char	*get_prompt(t_data *data, int mode)
{
	static char	prompt[PROMPT_LEN];
	static int	prefix_len;

	if (mode == 0)
	{
		ft_bzero(prompt, PROMPT_LEN);
		prefix_len = ft_strlcpy(prompt, data->prefix, PROMPT_LEN - SUFFIX_LEN);
	}
	if (mode == 1)
		return (prompt);
	if (mode == 2 && prefix_len < PROMPT_LEN)
	{
		add_pwd_to_prompt(data, prompt, prefix_len);
		ft_strlcat(prompt, PROMPT_SUFFIX, PROMPT_LEN);
	}
	return (prompt);
}
