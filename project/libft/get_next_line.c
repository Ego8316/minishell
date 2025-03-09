/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:45:39 by ego               #+#    #+#             */
/*   Updated: 2025/03/04 17:49:33 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Goes through the string s to search for
 * the first occurence of the character c. If found,
 * returns the position, -1 otherwise.
 * 
 * @param c Character to find.
 * @param s String to be searched.
 * 
 * @return Position of the character, -1 otherwise.
 */
static int	ft_char_in_str(char c, char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Frees a char pointer only if needed.
 * 
 * @param s Pointer to be freed.
 * 
 * @return NULL.
 */
static char	*ft_free(char *s)
{
	if (s)
		free(s);
	return (NULL);
}

/**
 * @brief Copies from the stash to the line up to a newline (included)
 * or everything if there is no newline in the stash. Shifts the stash
 * afterwards.
 * 
 * @param line Line string.
 * @param stash Stash string.
 * @param nl_pos Position of the newline in stash, -1 if none.
 * 
 * @return The new allocated line, NULL if allocation fails.
 */
static char	*copy_from_stash(char *line, char *stash, int nl_pos)
{
	char	*join;
	size_t	line_len;
	size_t	stash_len;
	size_t	append;

	line_len = ft_strlen_null(line);
	stash_len = ft_strlen_null(stash);
	if (nl_pos == -1)
		append = stash_len;
	else
		append = nl_pos + 1;
	join = (char *)malloc((line_len + append + 1) * sizeof(char));
	if (!join)
	{
		ft_memset(stash, 0, BUFFER_SIZE);
		return (ft_free(line));
	}
	ft_memmove(join, line, line_len);
	ft_free(line);
	ft_memmove(join + line_len, stash, append);
	join[line_len + append] = 0;
	ft_memmove(stash, stash + append, stash_len - append);
	ft_memset(stash + (stash_len - append), 0, append);
	return (join);
}

/**
 * @brief Reads the file and appends the content to the line until
 * finding a newline. In case of read or allocaton error, bzeros
 * the stash, frees the line and returns NULL.
 * 
 * @param fd The file descriptor to be read from.
 * @param line Line string.
 * @param stash Stash string.
 * 
 * @return The new line, NULL if allocation or read fails.
 */
static char	*get_to_next_nl(int fd, char *line, char *stash)
{
	ssize_t	r;
	int		nl_pos;

	r = 1;
	while (r > 0)
	{
		r = read(fd, stash, BUFFER_SIZE);
		if (r == -1)
		{
			ft_memset(stash, 0, BUFFER_SIZE);
			return (ft_free(line));
		}
		stash[r] = 0;
		if (r == 0)
			return (line);
		nl_pos = ft_char_in_str('\n', stash);
		line = copy_from_stash(line, stash, nl_pos);
		if (!line || nl_pos != -1)
			return (line);
	}
	return (line);
}

/**
 * @brief Reads from a file descriptor and gives the next line.
 * 
 * @param fd File descriptor to be read from.
 * 
 * @return The new allocated line. NULL if EOF is reached, file
 * descriptor is invalid or if allocation fails.
 */
char	*get_next_line(int fd)
{
	static char	stash[FD_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			nl_pos;

	if (fd < 0 || fd >= FD_MAX || read(fd, 0, 0) < 0 || BUFFER_SIZE < 1)
	{
		ft_memset(stash[fd], 0, BUFFER_SIZE);
		return (NULL);
	}
	line = NULL;
	nl_pos = ft_char_in_str('\n', stash[fd]);
	if (*stash[fd])
	{
		line = copy_from_stash(line, stash[fd], nl_pos);
		if (!line || nl_pos != -1)
			return (line);
	}
	return (get_to_next_nl(fd, line, stash[fd]));
}
