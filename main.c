#include "cub3d.h"




int main(int argc, char **argv)
{
	t_sceneData *data;
	
	// data = NULL;
	data = malloc(sizeof(t_sceneData));
	if(!data)
	{
		printf("Error\nMalloc failed\n");
		return (0);
	}
	check_arg(argc, argv);
	printf("argv[1]: %s\n", argv[1]);
	init_sceneData(data);
	read_scene(argv[1], data);
	// check_map_elm(data);
	check_scene(data);
	
	// get_scene(data);
	free(data);
	return (0);
}

void check_arg(int ac, char **av)
{
	// if (ac != 2)
	// {
	// 	printf("Usage: ./cub3d <map>");
	// 	exit(1);
	// }
	if (ac < 2)
	{
		printf("%s\n", VIOLET"You dont have enough arguments\n");
		exit(1);
	}
	if (!ft_strchr(av[1], '.'))
	{
		printf("%s\n", RED"Invalid File");
		exit(1);
	}
	
	if (ft_strncmp((ft_strrchr(av[1], '.')), ".cub", 5))
	{
		printf("%s\n", RED"invalid extension");
		exit(1);
	}
}

int open_file(char *file)
{
	int	fd;
	fd = open(file, O_RDONLY);

	if(fd == -1)
	{
		printf("%s\n", RED"No file to read"RESET);
		exit(0);
	}
	return(fd);
}

void    read_scene(char *file, t_sceneData *data)
{
    char *combined_map = NULL;
    char *current_line = NULL;
    char *temp_map = NULL;
	int fd;
	// data->scene = malloc(sizeof(char *) + 1);
	current_line = NULL;
	fd = open_file(file);
	combined_map = ft_strdup(""); // Allocate memory for a string to store the file contents, initialize with an empty string.
	while (1)
	{
		current_line = get_next_line(fd);
		if (current_line == NULL)
			break; // Exit the loop if no more lines can be read from the file.
		temp_map = combined_map;
		combined_map = ft_strjoin(temp_map, current_line);// Concatenate the new line to the existing file contents.
		free(temp_map);
		free(current_line);
	}
data->scene = ft_split(combined_map, '\n');
//print_scene(data);
free(combined_map);
free(current_line);
if (close(fd) == -1)
{
	printf("Error\nCould not close file %s.\n", file);
	exit(1);
}
get_scene(data);
// check_scene(data);
}

void	check_scene(t_sceneData	*data)
{
	// (void)data;
	printf("data->texture_field->pathhh%s\n",data->texture_field->path);
	valid_extension(data->texture_field->path);
	printf("data->north_texture %s\n",data->north_texture.path);
	check_texture(data);
	// printf("path\n");
	// check_color(data);
}
void	valid_extension(char *tex_path)
{
	int len;

	
	len = ft_strlen(tex_path);
	printf("tex_path: %s\n", tex_path);
	if (tex_path[len - 1] != 'm' || tex_path[len - 2] != 'p' || tex_path[len - 3] != 'x' || tex_path[len - 4] != '.')
	{
		printf ("%c\n", tex_path[len - 1]);
		printf("%s\n", RED"Error\nInvalid texture extension"RESET);
		exit(1);
	}
	// return (1);
}

void	check_texture(t_sceneData *data)
{
	// if(data->)north texture
	if (data->north_texture.path == NULL)
	{
		printf("%s\n", RED"Error\nNo north texture");
		exit(1);
	}
	if (data->south_texture.path == NULL)
	{
		printf("%s\n", RED"Error\nNo south texture");
		exit(1);
	}
	if (data->west_texture.path == NULL)
	{
		printf("%s\n", RED"Error\nNo west texture");
		exit(1);
	}
	if (data->east_texture.path == NULL)
	{
		printf("%s\n", RED"Error\nNo east texture");
		exit(1);
	}
}
// int main(int argc, char **argv)
// {
//     t_sceneData *data;
//     data = malloc(sizeof(t_sceneData));
//     if (!data)
//     {
//         printf("Error\nMalloc failed\n");
//         return (0);
//     }

//     check_arg(argc, argv);
//     printf("argv[1]: %s\n", argv[1]);
//     init_sceneData(data);
//     read_scene(argv[1], data);
    
//     // Extract and print map lines
//     extract_map_lines(data);
    
//     // Continue with the rest of your logic
//     // ...
    
//     free(data);
//     return (0);
// }


void	print_scene(t_sceneData *data)
{
	int i;


	i = 0;
	while (data->scene[i])
	{
		
		printf( "print_scene: %s", data->scene[i]);
		printf("\n");
		i++;
	}
	printf("print_scene: %s\n", data->scene[i]);
	
}

// void    get_map(const char *line_map, t_map *map_data, t_sceneData *data)
// {
//     int i;

//     //Intialize map width and height
   
//     map_data->m_width = ft_strlen(line_map);

//     map_data->m_height = 0;

//    // memmory allocation for map
//    printf("map_data->map: %p\n", map_data->map);
//     map_data->map = (char **)malloc(sizeof(char *));
//     map_data->map[0] = strdup(line_map);
//    printf("map_data->map2: %s\n", map_data->map[0]);
//     map_data->m_height++;
//     //get the rest of the map
//     i = 0;
//     // printf("data->scene[i]1: %s\n", data->scene[i]);
//    printf("before data->scene[i]: %s\n", data->scene[i]);

//     while (data->scene[i] != NULL)
//     {
//         if (data->scene[i][0] == '\0')
//         {
//             printf("Error: Empty line in map.\n");
//             exit(EXIT_FAILURE);
//         }
//         else
//         {

//             map_data->m_height++;
//             //resize map array
//             map_data->map = (char **)realloc(map_data->map, map_data->m_height * sizeof(char *));
//             // Allocate memory and store the map line
//             map_data->map[map_data->m_height - 1] = strdup(data->scene[i]);
//         }
//         i++;
//         // printf("data->scene[i]: %s\n", data->scene[i]);
//     }
  
//    printf("data->scene[i]: %s\n", data->scene[i]);
// }



// //note what to continue
// //first check if its valid scene
