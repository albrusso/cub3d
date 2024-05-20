/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:53:05 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/19 13:48:56 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex1(unsigned long long nbr, char *hex, t_sc *sc)
{
	if (nbr >= 16)
	{
		ft_puthex1(nbr / 16, hex, sc);
		ft_putchar(hex[nbr % 16], sc);
	}
	if (nbr < 16)
	{
		ft_putchar(hex[nbr], sc);
	}
}

void	ft_pointer(va_list arg, t_sc *sc)
{
	unsigned long	c;

	c = va_arg(arg, unsigned long);
	if (!c)
		sc->len += write (1, "(nil)", 5);
	else
	{
		sc->len += write (1, "0x", 2);
		ft_puthex1(c, "0123456789abcdef", sc);
	}
}
