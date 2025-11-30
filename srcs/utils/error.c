/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:14:21 by ego               #+#    #+#             */
/*   Updated: 2025/05/22 20:36:02 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints up to three strings to stderr and returns the given status.
 * 
 * @param s1 First string to be printed.
 * @param s2 Second string to be printed.
 * @param s3 Third string to be printed.
 * @param status Error code.
 * 
 * @return The error code.
 */
int	errmsg(char *s1, char *s2, char *s3, int status)
{
	if (s1)
		ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
		ft_putstr_fd(s2, STDERR_FILENO);
	if (s3)
		ft_putstr_fd(s3, STDERR_FILENO);
	return (status);
}

/**
 * @brief Prints "minishell: <s1>: <s2>" to stderr and returns the status.
 * 
 * @param s1 Fist string to be displayed.
 * @param s2 Second string to be displayed.
 * @param status Exit code.
 * 
 * @return Error's number.
 */
int	errmsg_prefix(char *s1, char *s2, int status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(s2, STDERR_FILENO);
	return (status);
}

/**
 * @brief Prints "minishell: <s>: strerror(errnum)" to stderr and returns
 * errnum.
 * 
 * @param prefix Whether to print "minishell: " or not.
 * @param s String corresponding to what caused the error.
 * @param errnum Error's number.
 * 
 * @return Error's number.
 */
int	errmsg_errnum(int prefix, char *s, int errnum)
{
	if (prefix)
		ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errnum == CMD_IS_DIR)
	{
		errnum += 1;
		ft_putendl_fd(CMD_IS_DIR_MSG, STDERR_FILENO);
	}
	else if (errnum == CMD_NOT_EXEC)
		ft_putendl_fd(CMD_NOT_EXEC_MSG, STDERR_FILENO);
	else if (errnum == CMD_NOT_FOUND)
		ft_putendl_fd(CMD_NOT_FOUND_MSG, STDERR_FILENO);
	else
		ft_putendl_fd(strerror(errnum), STDERR_FILENO);
	return (errnum);
}
