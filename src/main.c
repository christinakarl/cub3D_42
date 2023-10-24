/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarl <ckarl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:02:52 by ckarl             #+#    #+#             */
/*   Updated: 2023/10/23 21:40:47 by ckarl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	game->data = malloc(sizeof(t_sceneData));
	if(!game->data)
	{
		printf("Error\nMalloc failed\n");
		return (0);
	}
	check_arg(argc, argv);
	// printf("after check arg\n");
	init_sceneData(game->data);
	// printf("after scene data\n");
	read_scene(argv[1], game->data);
	// printf("after read scene\n");
	get_scene(game->data);
	// printf("after get scene\n");
	check_scene(game->data);
	// printf("after check scene\n");
	init_mlx_win(game);
	// printf("after init mlx\n");
	free_map_data(&(game->data->map_data));
	free(game->data);
	free(game);
	return (0);
}

void	check_arg(int ac, char **av)
{
	if (ac < 2)
	{
		printf("Error\n");
		printf("%s\n", VIOLET"Too few arguments\n");
		exit(1);
	}
	if (ac > 2)
	{
		printf("Error\n");
		printf("%s\n", VIOLET"Too many arguments\n");
		exit(1);
	}
	if (!ft_strchr(av[1], '.'))
	{
		printf("Error\n");
		printf("%s\n", RED"Invalid File");
		exit(1);
	}
	if (ft_strncmp((ft_strrchr(av[1], '.')), ".cub", 5))
	{
		printf("Error\n");
		printf("%s\n", RED"invalid extension");
		exit(1);
	}
}

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		printf("%s\n", RED"No file to read"RESET);
		exit(0);
	}
	return (fd);
}

void	read_scene(char *file, t_sceneData *data)
{
	char *combined_map = NULL;
	char *current_line;
	char *temp_map = NULL;
	int fd;

	current_line = NULL;
	fd = open_file(file);
	combined_map = ft_strdup("");// Allocate memory for a string to store the file contents, initialize with an empty string.
	if(!combined_map)
		return;
	while (1)
	{
		current_line = get_next_line(fd);
		if (current_line == NULL)
			break ; // Exit the loop if no more lines can be read from the file.
		temp_map = combined_map;
		combined_map = ft_strjoin(temp_map, current_line);// Concatenate the new line to the existing file contents.
		free(temp_map);
		free(current_line);
	}
	data->scene = ft_split(combined_map, '\n');
	print_scene(data);
	// printf("after print scene\n");
	free(combined_map);
	free(current_line);
	close_file(fd);
}

int	close_file(int fd)
{
	if (close(fd) == -1)
	{
		printf("Error\nCould not close file.\n");
		exit(1);
	}
	return (0);
}
