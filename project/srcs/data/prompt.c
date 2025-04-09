/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:33:19 by ego               #+#    #+#             */
/*   Updated: 2025/04/09 15:44:51 by ego              ###   ########.fr       */
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
static char	*get_hostname()
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
static char	*get_user()
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
char	*get_prefix()
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

// /**
//  * @brief Builds the full prompt.
//  */
// char	*get_prompt(t_data *data, int mode)
// {
// 	static char	prefix[MAX_PROMPT_SIZE];


// }
