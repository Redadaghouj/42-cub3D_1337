/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:42:54 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/24 02:03:10 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	prev_res;	

	res = 0;
	i = 0;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		prev_res = res;
		res = res * 10 + (nptr[i] - '0');
		if (prev_res > res)
			return (-1);
		i++;
	}
	return (res);
}
