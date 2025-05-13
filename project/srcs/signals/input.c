/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkurt <idkmymailngl@mail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:41:03 by pkurt             #+#    #+#             */
/*   Updated: 2025/03/12 16:48:43 by pkurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios	init_input(void)
{
	struct termios	termios_p;
	struct termios	og_termios_p;

	tcgetattr(0, &og_termios_p);
	tcgetattr(0, &termios_p);
	termios_p.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
			| INLCR | IGNCR | ICRNL | IXON);
	termios_p.c_oflag &= ~OPOST;
	termios_p.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	termios_p.c_cflag &= ~(CSIZE | PARENB);
	termios_p.c_cflag |= CS8;
	tcsetattr(0, 0, &termios_p);
	return (og_termios_p);
}

static int	try_read_input(char **str)
{
	char	c;
	int		rr;

	rr = read(0, &c, 1);
	if (rr != 1)
		return (0);
	if (c == 13)
		return (0);
	if (c == 127)
	{
		if (ft_strlen_null(*str) == 0)
			return (1);
		ft_putstr_fd("\b \b", 1);
		*str = str_remove_free(*str, 1);
		return (1);
	}
	ft_putchar_fd(c, 1);
	*str = str_append_free(*str, c);
	return (1);
}

char	*read_term_line(const char *prompt)
{
	char			*res;
	struct termios	termios_p;

	res = 0;
	ft_putstr_fd(prompt, 0);
	if (!isatty(0))
		return (readline(0));
	termios_p = init_input();
	while (try_read_input(&res))
		;
	tcsetattr(0, 0, &termios_p);
	ft_putstr_fd("\n", 0);
	if (!res)
		return (strb_new());
	return (res);
}
