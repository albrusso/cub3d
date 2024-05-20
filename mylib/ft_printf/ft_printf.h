/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:54:33 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/19 14:07:00 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "../libft/libft.h"

typedef struct s_sc
{
	int	len;
}	t_sc;

void	ft_char(va_list arg, t_sc *sc);

void	ft_int(va_list arg, t_sc *sc);

void	ft_string(va_list arg, t_sc *sc);

void	ft_hexadecimal(va_list arg, t_sc *sc, const char format);

void	ft_putchar(char c, t_sc *sc);

void	ft_putstr(char *str, t_sc *sc);

void	ft_putnbr(long int nbr, t_sc *sc);

int		ft_intlen(int nbr);

int		ft_printf(const char *format, ...);

void	ft_pointer(va_list arg, t_sc *sc);

void	ft_puthex(unsigned int nbr, char *hex, t_sc *sc);

void	ft_putnbru(unsigned int nb, t_sc *sc);

void	ft_unsigned(va_list arg, t_sc *sc);

#endif
