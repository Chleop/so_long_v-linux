/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 11:24:21 by cproesch          #+#    #+#             */
/*   Updated: 2021/09/23 12:11:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(int x, int y, t_data *data)
{
	char	code;
	void	*mlx;
	void	*win;

	code = data->map_tab[y][x];
	mlx = data->mlx_ptr;
	win = data->win_ptr;
	if (code == '0')
		mlx_put_image_to_window (mlx, win, data->pic_back, x * 60, y * 60);
	if (code == '1')
		mlx_put_image_to_window (mlx, win, data->pic_wall, x * 60, y * 60);
	if (code == 'E')
		mlx_put_image_to_window (mlx, win, data->pic_exit, x * 60, y * 60);
	if (code == 'C')
		mlx_put_image_to_window (mlx, win, data->pic_coll, x * 60, y * 60);
	if (code == 'P')
		mlx_put_image_to_window (mlx, win, data->pic_player, x * 60, y * 60);
}

int	images_to_window(t_data *data)
{
	size_t	x;
	size_t	y;
	int		i;

	i = 0;
	y = -1;
	while (++y < data->map_length)
	{
		x = -1;
		while (++x < data->map_width)
			put_image(x, y, data);
	}
	return (0);
}

int	key_event(int keypress, t_data *data)
{
	char	next_p;

	if ((keypress == ESC) || (keypress == W) || (keypress == A)
		|| (keypress == S) || (keypress == D))
	{
		next_p = set_next_p (keypress, data);
		if (next_p != '1')
		{
			if (!is_exit(next_p, data))
				make_mouv(next_p, keypress, data);
		}
	}
	return (0);
}

int	redcross_exit(t_data *data)
{
	ft_exit(data, 1);
	return (1);
}

void	display_game(t_data data)
{
	data.mouv = 0;
	mlx_loop_hook(data.mlx_ptr, &images_to_window, &data);
	mlx_key_hook(data.win_ptr, &key_event, &data);
	mlx_hook(data.win_ptr, 17, 0, &redcross_exit, &data);
	mlx_loop(data.mlx_ptr);
}
