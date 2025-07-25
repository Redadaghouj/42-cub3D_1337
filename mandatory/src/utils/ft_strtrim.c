/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:14:37 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/25 04:14:11 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	skip_leading_spaces(char *line)
{
	int	start;

	start = 0;
	while (line[start])
	{
		if (line[start] != ' ')
			break ;
		start++;
	}
	return (start);
}

int	skip_trailing_spaces(char *line)
{
	int	end;

	end = ft_strlen(line) - 1;
	while (end > 0)
	{
		if (line[end] != ' ')
			break ;
		end--;
	}
	return (end);
}

char	*ft_strtrim(char *line)
{
	int	start;
	int	end;

	start = skip_leading_spaces(line);
	end = skip_trailing_spaces(line);
	return (ft_substr(line, start, end - start + 1));
}
