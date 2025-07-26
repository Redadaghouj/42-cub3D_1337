/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_cursor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <main@w2wizard.dev>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 20:10:54 by W2Wizard      #+#    #+#                 */
/*   Updated: 2023/03/09 11:11:45 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.hh"

//= Public =//

t_mlx_win_cursor_t* mlx_create_std_cursor(t_cursor type)
{
	MLX_ASSERT(type >= MLX_CURSOR_ARROW && type < MLX_CURSOR_VRESIZE, "Invalid standard cursor type");

	GLFWcursor* cursor;
	if ((cursor = glfwCreateStandardCursor(type)))
		return (cursor);
	return ((void *)mlx_error(MLX_MEMFAIL));
}

t_mlx_win_cursor_t* mlx_create_cursor(t_mlx_texture* texture)
{
	MLX_NONNULL(texture);

	GLFWcursor* cursor;
	GLFWimage image = (GLFWimage) {
		.width = texture->width,
		.height = texture->height,
		.pixels = texture->pixels
	};

	if ((cursor = glfwCreateCursor(&image, 0, 0)))
		return (cursor);
	return ((void *)mlx_error(MLX_MEMFAIL));
}

void mlx_destroy_cursor(t_mlx_win_cursor_t* cursor)
{
	MLX_NONNULL(cursor);

	glfwDestroyCursor(cursor);
}

void mlx_set_cursor(t_mlx* mlx, t_mlx_win_cursor_t* cursor)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(cursor);

	glfwSetCursor(mlx->window, cursor);
}

void mlx_set_cursor_mode(t_mlx* mlx, t_mouse_mode mode)
{
	MLX_NONNULL(mlx);

	glfwSetInputMode(mlx->window, GLFW_CURSOR, mode);
}
