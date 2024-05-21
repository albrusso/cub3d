/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:52:57 by albrusso          #+#    #+#             */
/*   Updated: 2024/03/19 13:49:09 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbru(unsigned int nb, t_sc *sc)
{
	if (nb >= 10)
	{
		ft_putnbru(nb / 10, sc);
		nb = nb % 10;
	}
	if (nb < 10)
		ft_putchar(nb + 48, sc);
}

void	ft_unsigned(va_list arg, t_sc *sc)
{
	unsigned int	n;

	n = va_arg(arg, unsigned int);
	ft_putnbru(n, sc);
}
