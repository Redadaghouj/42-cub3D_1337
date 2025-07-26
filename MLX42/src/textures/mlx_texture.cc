/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_texture.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <main@w2wizard.dev>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 01:02:24 by W2Wizard      #+#    #+#                 */
/*   Updated: 2023/03/09 11:03:47 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.hh"

//= Public =//

t_mlx_image* mlx_texture_to_image(t_mlx* mlx, t_mlx_texture* texture)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(texture);

	t_mlx_image* image = mlx_new_image(mlx, texture->width, texture->height);
	if (image == NULL)
		return (NULL);

	uint8_t* pixelx;
	uint8_t* pixeli;
	for (uint32_t i = 0; i < texture->height; i++)
	{
		pixelx = &texture->pixels[(i * texture->width) * texture->bytes_per_pixel];
		pixeli = &image->pixels[(i * image->width) * texture->bytes_per_pixel];
		memmove(pixeli, pixelx, texture->width * texture->bytes_per_pixel);
	}
	return (image);
}

void mlx_delete_texture(t_mlx_texture* texture)
{
	MLX_NONNULL(texture);

	mlx_freen(2, texture->pixels, texture);
}
