/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MLX42.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2wizard <main@w2wizard.dev>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 01:14:59 by W2wizard      #+#    #+#                 */
/*   Updated: 2022/11/22 09:06:54 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX42_H
# define MLX42_H
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# ifdef __cplusplus

extern "C"

{
# endif
typedef enum action
{
	MLX_RELEASE = 0,
	MLX_PRESS = 1,
	MLX_REPEAT = 2,
} action_t;
typedef enum modifier_key
{
	MLX_SHIFT = 0x0001,
	MLX_CONTROL = 0x0002,
	MLX_ALT = 0x0004,
	MLX_SUPERKEY = 0x0008,
	MLX_CAPSLOCK = 0x0010,
	MLX_NUMLOCK = 0x0020,
}	t_modifier_key;
typedef enum mouse_key
{
	MLX_MOUSE_BUTTON_LEFT = 0,
	MLX_MOUSE_BUTTON_RIGHT = 1,
	MLX_MOUSE_BUTTON_MIDDLE = 2,
}	t_mouse_key;
typedef enum mouse_mode
{
	MLX_MOUSE_NORMAL = 0x00034001,
	MLX_MOUSE_HIDDEN = 0x00034002,
	MLX_MOUSE_DISABLED = 0x00034003,
}	t_mouse_mode;
typedef enum cursor
{
	MLX_CURSOR_ARROW = 0x00036001,
	MLX_CURSOR_IBEAM = 0x00036002,
	MLX_CURSOR_CROSSHAIR = 0x00036003,
	MLX_CURSOR_HAND = 0x00036004,
	MLX_CURSOR_HRESIZE = 0x00036005,
	MLX_CURSOR_VRESIZE = 0x00036006,
}	t_cursor;
typedef enum keys
{
	MLX_KEY_SPACE = 32,
	MLX_KEY_APOSTROPHE = 39,
	MLX_KEY_COMMA = 44,
	MLX_KEY_MINUS = 45,
	MLX_KEY_PERIOD = 46,
	MLX_KEY_SLASH = 47,
	MLX_KEY_0 = 48,
	MLX_KEY_1 = 49,
	MLX_KEY_2 = 50,
	MLX_KEY_3 = 51,
	MLX_KEY_4 = 52,
	MLX_KEY_5 = 53,
	MLX_KEY_6 = 54,
	MLX_KEY_7 = 55,
	MLX_KEY_8 = 56,
	MLX_KEY_9 = 57,
	MLX_KEY_SEMICOLON = 59,
	MLX_KEY_EQUAL = 61,
	MLX_KEY_A = 65,
	MLX_KEY_B = 66,
	MLX_KEY_C = 67,
	MLX_KEY_D = 68,
	MLX_KEY_E = 69,
	MLX_KEY_F = 70,
	MLX_KEY_G = 71,
	MLX_KEY_H = 72,
	MLX_KEY_I = 73,
	MLX_KEY_J = 74,
	MLX_KEY_K = 75,
	MLX_KEY_L = 76,
	MLX_KEY_M = 77,
	MLX_KEY_N = 78,
	MLX_KEY_O = 79,
	MLX_KEY_P = 80,
	MLX_KEY_Q = 81,
	MLX_KEY_R = 82,
	MLX_KEY_S = 83,
	MLX_KEY_T = 84,
	MLX_KEY_U = 85,
	MLX_KEY_V = 86,
	MLX_KEY_W = 87,
	MLX_KEY_X = 88,
	MLX_KEY_Y = 89,
	MLX_KEY_Z = 90,
	MLX_KEY_LEFT_BRACKET = 91,
	MLX_KEY_BACKSLASH = 92,
	MLX_KEY_RIGHT_BRACKET = 93,
	MLX_KEY_GRAVE_ACCENT = 96,
	MLX_KEY_ESCAPE = 256,
	MLX_KEY_ENTER = 257,
	MLX_KEY_TAB = 258,
	MLX_KEY_BACKSPACE = 259,
	MLX_KEY_INSERT = 260,
	MLX_KEY_DELETE = 261,
	MLX_KEY_RIGHT = 262,
	MLX_KEY_LEFT = 263,
	MLX_KEY_DOWN = 264,
	MLX_KEY_UP = 265,
	MLX_KEY_PAGE_UP = 266,
	MLX_KEY_PAGE_DOWN = 267,
	MLX_KEY_HOME = 268,
	MLX_KEY_END = 269,
	MLX_KEY_CAPS_LOCK = 280,
	MLX_KEY_SCROLL_LOCK = 281,
	MLX_KEY_NUM_LOCK = 282,
	MLX_KEY_PRINT_SCREEN = 283,
	MLX_KEY_PAUSE = 284,
	MLX_KEY_F1 = 290,
	MLX_KEY_F2 = 291,
	MLX_KEY_F3 = 292,
	MLX_KEY_F4 = 293,
	MLX_KEY_F5 = 294,
	MLX_KEY_F6 = 295,
	MLX_KEY_F7 = 296,
	MLX_KEY_F8 = 297,
	MLX_KEY_F9 = 298,
	MLX_KEY_F10 = 299,
	MLX_KEY_F11 = 300,
	MLX_KEY_F12 = 301,
	MLX_KEY_F13 = 302,
	MLX_KEY_F14 = 303,
	MLX_KEY_F15 = 304,
	MLX_KEY_F16 = 305,
	MLX_KEY_F17 = 306,
	MLX_KEY_F18 = 307,
	MLX_KEY_F19 = 308,
	MLX_KEY_F20 = 309,
	MLX_KEY_F21 = 310,
	MLX_KEY_F22 = 311,
	MLX_KEY_F23 = 312,
	MLX_KEY_F24 = 313,
	MLX_KEY_F25 = 314,
	MLX_KEY_KP_0 = 320,
	MLX_KEY_KP_1 = 321,
	MLX_KEY_KP_2 = 322,
	MLX_KEY_KP_3 = 323,
	MLX_KEY_KP_4 = 324,
	MLX_KEY_KP_5 = 325,
	MLX_KEY_KP_6 = 326,
	MLX_KEY_KP_7 = 327,
	MLX_KEY_KP_8 = 328,
	MLX_KEY_KP_9 = 329,
	MLX_KEY_KP_DECIMAL = 330,
	MLX_KEY_KP_DIVIDE = 331,
	MLX_KEY_KP_MULTIPLY = 332,
	MLX_KEY_KP_SUBTRACT = 333,
	MLX_KEY_KP_ADD = 334,
	MLX_KEY_KP_ENTER = 335,
	MLX_KEY_KP_EQUAL = 336,
	MLX_KEY_LEFT_SHIFT = 340,
	MLX_KEY_LEFT_CONTROL = 341,
	MLX_KEY_LEFT_ALT = 342,
	MLX_KEY_LEFT_SUPER = 343,
	MLX_KEY_RIGHT_SHIFT = 344,
	MLX_KEY_RIGHT_CONTROL = 345,
	MLX_KEY_RIGHT_ALT = 346,
	MLX_KEY_RIGHT_SUPER = 347,
	MLX_KEY_MENU = 348,
}	t_keys;
typedef struct mlx_texture
{
	uint32_t		width;
	uint32_t		height;
	uint8_t			bytes_per_pixel;
	uint8_t			*pixels;
}	t_mlx_texture;
typedef struct xpm
{
	t_mlx_texture	texture;
	int32_t			color_count;
	int32_t			cpp;
	char			mode;
}	t_xpm;
typedef struct mlx_instance
{
	int32_t			x;
	int32_t			y;
	int32_t			z;
	bool			enabled;
}	t_mlx_instance;
typedef struct mlx_key_data
{
	t_keys			key;
	action_t		action;
	int32_t			os_key;
	t_modifier_key	modifier;
}	t_mlx_key_data;
typedef struct mlx_image
{
	const uint32_t	width;
	const uint32_t	height;
	uint8_t			*pixels;
	t_mlx_instance	*instances;
	size_t			count;
	bool			enabled;
	void			*context;
}	t_mlx_image;
typedef struct mlx
{
	void			*window;
	void			*context;
	int32_t			width;
	int32_t			height;
	double			delta_time;
}	t_mlx;
typedef enum g_mlx_errno
{
	MLX_SUCCESS = 0,
	MLX_INVEXT,
	MLX_INVFILE,
	MLX_INVPNG,
	MLX_INVXPM,
	MLX_INVPOS,
	MLX_INVDIM,
	MLX_INVIMG,
	MLX_VERTFAIL,
	MLX_FRAGFAIL,
	MLX_SHDRFAIL,
	MLX_MEMFAIL,
	MLX_GLADFAIL,
	MLX_GLFWFAIL,
	MLX_WINFAIL,
	MLX_STRTOOBIG,
	MLX_ERRMAX,
}	t_mlx_errno;
extern t_mlx_errno	g_mlx_errno;
typedef enum mlx_settings
{
	MLX_STRETCH_IMAGE = 0,
	MLX_FULLSCREEN,
	MLX_MAXIMIZED,
	MLX_DECORATED,
	MLX_HEADLESS,
	MLX_SETTINGS_MAX,
}	t_mlx_settings;
typedef void		(*t_mlx_scrollfunc)(double xdelta, double ydelta,
			void *param);
typedef void		(*t_mlx_mousefunc)(t_mouse_key button, action_t action,
			t_modifier_key mods, void *param);
typedef void		(*t_mlx_cursorfunc)(double xpos, double ypos,
			void *param);
typedef void		(*t_mlx_keyfunc)(t_mlx_key_data keydata, void *param);
typedef void		(*t_mlx_resizefunc)(int32_t width, int32_t height,
			void *param);
typedef void		(*t_mlx_closefunc)(void *param);
typedef void		t_mlx_win_cursor_t;
const char			*mlx_strerror(t_mlx_errno val);
t_mlx				*mlx_init(int32_t width, int32_t height, const char *title,
						bool resize);
void				mlx_set_setting(t_mlx_settings setting, int32_t value);
void				mlx_close_window(t_mlx *mlx);
void				mlx_loop(t_mlx *mlx);
void				mlx_set_icon(t_mlx *mlx, t_mlx_texture *image);
void				mlx_terminate(t_mlx *mlx);
double				mlx_get_time(void);
void				mlx_focus(t_mlx *mlx);
void				mlx_get_monitor_size(int32_t index,
						int32_t *width, int32_t *height);
void				mlx_set_window_pos(t_mlx *mlx, int32_t xpos, int32_t ypos);
void				mlx_get_window_pos(t_mlx *mlx,
						int32_t *xpos, int32_t *ypos);
void				mlx_set_window_size(t_mlx *mlx,
						int32_t new_width, int32_t new_height);
void				mlx_set_window_title(t_mlx *mlx, const char *title);
bool				mlx_is_key_down(t_mlx *mlx, t_keys key);
bool				mlx_is_mouse_down(t_mlx *mlx, t_mouse_key key);
void				mlx_get_mouse_pos(t_mlx *mlx, int32_t *x, int32_t *y);
void				mlx_set_mouse_pos(t_mlx *mlx, int32_t x, int32_t y);
void				mlx_set_cursor_mode(t_mlx *mlx, t_mouse_mode mode);
t_mlx_win_cursor_t	*mlx_create_std_cursor(t_cursor type);
t_mlx_win_cursor_t	*mlx_create_cursor(t_mlx_texture *texture);
void				mlx_destroy_cursor(t_mlx_win_cursor_t *cursor);
void				mlx_set_cursor(t_mlx *mlx, t_mlx_win_cursor_t *cursor);
void				mlx_scroll_hook(t_mlx *mlx, t_mlx_scrollfunc func,
						void *param);
void				mlx_mouse_hook(t_mlx *mlx, t_mlx_mousefunc func,
						void *param);
void				mlx_cursor_hook(t_mlx *mlx, t_mlx_cursorfunc func,
						void *param);
void				mlx_key_hook(t_mlx *mlx, t_mlx_keyfunc func,
						void *param);
void				mlx_close_hook(t_mlx *mlx, t_mlx_closefunc func,
						void *param);
void				mlx_resize_hook(t_mlx *mlx, t_mlx_resizefunc func,
						void *param);
bool				mlx_loop_hook(t_mlx *mlx, void (*f)(void *), void *param);
t_mlx_texture		*mlx_load_png(const char *path);
t_xpm				*mlx_load_xpm42(const char *path);
void				mlx_delete_texture(t_mlx_texture *texture);
void				mlx_delete_xpm42(t_xpm *xpm);
t_mlx_image			*mlx_texture_to_image(t_mlx *mlx, t_mlx_texture *texture);
void				mlx_put_pixel(t_mlx_image *image, uint32_t x, uint32_t y,
						uint32_t color);
t_mlx_image			*mlx_new_image(t_mlx *mlx, uint32_t width, uint32_t height);
int32_t				mlx_image_to_window(t_mlx *mlx, t_mlx_image *img, int32_t x,
						int32_t y);
void				mlx_delete_image(t_mlx *mlx, t_mlx_image *image);
bool				mlx_resize_image(t_mlx_image *img, uint32_t nwidth,
						uint32_t nheight);
void				mlx_set_instance_depth(t_mlx_instance *instance,
						int32_t zdepth);
t_mlx_image			*mlx_put_string(t_mlx *mlx, const char *str, int32_t x,
						int32_t y);
const				t_mlx_texture	*mlx_get_font(void);
int32_t				mlx_get_texoffset(char c);
#  ifdef __cplusplus

}

#  endif
# endif