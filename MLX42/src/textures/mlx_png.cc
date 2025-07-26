/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_png.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <main@w2wizard.dev>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 23:11:29 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/06/27 19:55:06 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.hh"

//= Public =//

t_mlx_texture* mlx_load_png(const char* path)
{
	MLX_NONNULL(path);

	t_mlx_texture* image;
	if (!(image = malloc(sizeof(t_mlx_texture))))
		return ((void*)mlx_error(MLX_MEMFAIL));

	uint32_t error;
	image->bytes_per_pixel = BPP;
	if ((error = lodepng_decode32_file(&image->pixels, &image->width, &image->height, path)))
	{
		free(image);
		// Explicitly print error on purpose
		fprintf(stderr, "MLX42: LodePNG: %s\n", lodepng_error_text(error));
		return ((void*)mlx_error(MLX_INVPNG));
	}
	return (image);
}
