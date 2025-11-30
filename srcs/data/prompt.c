/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:33:19 by ego               #+#    #+#             */
/*   Updated: 2025/04/11 04:41:24 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Tries to retrieve the hostname from the /etc/hostname file. Reads the
 * file using `get_next_line`. If the file cannot be found, sets the hostname
 * to "42" by default. Adds color formatting to the hostname.
 * 
 * @return Allocated copy of the hostname with color formatting, NULL if
 * memory allocation fails.
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
 * @brief Tries to retrieve the current user from the environment variables.
 * If not found or if it is empty, sets the user to "user" by default. Adds
 * color formatting to the user string.
 * 
 * @return Allocated copy of the user with color formatting, NULL if memory
 * allocation fails.
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
 * @brief Builds the full prompt prefix of the form "user@hostname:". This is
 * a combination of the user and hostname with added color formatting.
 * 
 * @return Allocated string representing the prefix, NULL if memory allocation
 * fails.
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
 * @brief Adds the current working directory (PWD) to the prompt. If PWD is not
 * found in the environment, it uses the backup stored in the data structure.
 * If HOME is set, replace the home directory path with a '~'.
 * 
 * @param data Pointer to the main data structure.
 * @param prompt Prompt buffer to which the PWD will be added.
 * @param prefix_len Length of the prefix already in the prompt.
 * 
 * @return The length of whatever the function has attempted to copy into the
 * buffer.
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
 * @brief Builds the full prompt by assembling the prefix, current working
 * directory (PWD), and suffix. The `mode` argument controls the behavior
 * of the function:
 * @brief - 0: Builds the prompt.
 * @brief - 1: Returns the current prompt.
 * @brief - 2: Updates the prompt with the current working directory.
 * 
 * @param data Pointer to the main data structure.
 * @param mode Mode that determines what action to perform (0, 1, or 2).
 * 
 * @return The constructed prompt as a static string.
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
