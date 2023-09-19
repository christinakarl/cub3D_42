#include "../../cub3d.h"
#include "../../parser.h"

#include <string.h>

    // {"S", parse_resolution},
    // {"R", parse_resolution},
IdentifierParser parsers[] = {
    {"R", (void *)parse_resolution},
    {"NO", (void *)&parse_texture},
    {"SO", (void *)&parse_texture},
    {"WE", (void *)&parse_texture},
    {"EA", (void *)&parse_texture},
    {"F", (void *)&parse_color},
    {"C", (void *)&parse_color},

};
 /*if(!ft_strcmp(parsers[i].identifier, "R") )
                parse_resolution(str, &data->resolution);
            else*/
static void check_identifiers(char *identifier, char *str, t_sceneData *data, int i)
{
    if (!ft_strcmp(identifier, parsers[i].identifier))
        {
             if(!ft_strcmp(parsers[i].identifier, "R") )
                parse_resolution(str, &data->resolution);
            else if(!ft_strcmp(parsers[i].identifier, "NO") )
                parse_texture(str, &data->north_texture);
            else if(!ft_strcmp(parsers[i].identifier, "SO"))
                parse_texture(str, &data->south_texture);
            else if(!ft_strcmp(parsers[i].identifier, "WE"))
                parse_texture(str, &data->west_texture);
            else if(!ft_strcmp(parsers[i].identifier, "EA"))
                parse_texture(str, &data->east_texture);
            else if(!ft_strcmp(parsers[i].identifier, "F"))
                parse_color(str, &data->floor_color);
            else if(!ft_strcmp(parsers[i].identifier, "C"))
                parse_color(str, &data->ceiling_color);
            else
            {
                printf("Error\n");
                printf("Unknown identifier: %s\n", identifier);
                exit(EXIT_FAILURE);
            }
            return; // Exit after finding and calling the parser
        }
}
void get_file(char *identifier, char *str, t_sceneData *data)
{
    size_t i;

    i = -1;
    while(++i < sizeof(parsers) / sizeof(parsers[0]))
    {
        check_identifiers(identifier, str, data, i);
    
    }
}

void    check_reso(t_resolution *reso)
{
    if (reso->width <= 0 || reso->height <= 0)
    {
        printf(RED"Error\n"RESET);
        ft_error_msg(RED"Resolution is not set."RESET);
    }
    else if (reso->width > MAX_RES_WIDTH || reso->height > MAX_RES_HEIGHT)
    {
        printf("Error\n");
        ft_error_msg(RED"Resolution is too high.\n"RESET);
    }
    else
        printf(GREEN"Resolution is set.\n"RESET);
}

void parse_resolution(const char *str, t_resolution *reso) {
    char **strs_split;
    strs_split = ft_split(str, ' ');

    printf("Parsed parts: [%s], [%s]\n", strs_split[0], strs_split[1]);

    if (!ft_isdigit_strict(strs_split[0]) || !ft_isdigit_strict(strs_split[1])) {
        printf("Error\n");
        printf(RED "Invalid resolution format.\n" RESET);
        exit(EXIT_FAILURE);
    }

    reso->width = ft_atoi(strs_split[0]);
    reso->height = ft_atoi(strs_split[1]);

    printf("Parsed width: %d\n", reso->width);
    printf("Parsed height: %d\n", reso->height);
}

// void    parse_resolution(const char *str, t_resolution *reso)
// {
//     char **strs_split;
//     strs_split = ft_split(str, ' ');
//     printf("parse_resolution: %s\n", strs_split[0]);
//     printf("parse_resolution: %s\n", strs_split[1]);
//     empty_reso(strs_split[0]);
//     printf("parse_resolution: %s\n", strs_split[0]);
//     empty_reso(strs_split[1]);
//     printf("parse_resolution: %s\n", strs_split[1]);
//     if (!ft_isdigit_strict(strs_split[0]) || !ft_isdigit_strict(strs_split[1]))
//     {
//         printf("Error\n");
//         printf(RED"Invalid resolution format.\n"RESET);
//         exit(EXIT_FAILURE);
//     }
//     reso->width = ft_atoi(strs_split[0]);
//     reso->height = ft_atoi(strs_split[1]);
//     printf("parse_resolution width: %d\n", reso->width);
//     printf("parse_resolution height: %d\n", reso->height);
// }

void parse_texture(const char *str, t_texture *texture)
{
    if (str == NULL)
    {
        printf("Error\n");
        printf(RED"Texture path is NULL.\n"RESET);
        exit(EXIT_FAILURE);
    }
    if(!texture->path)
    {
        texture->path = ft_strdup_const(str);
        texture->path = ft_strtrim(texture->path, " ");
        texture->tex_height = 64;
        texture->tex_width = 64;
        if(!texture->path)
        {
            printf("Error\nCould not allocate memory for texture path.\n");
            exit(EXIT_FAILURE);
        }
        printf("parse_texture: %s\n", texture->path);

    }
    else
        texture->path = 0;

}

static void    color_split(char **strs_split, t_color *color)
{
    if (strs_split[0] && strs_split[1] && strs_split[2] &&
        ft_isdigit_strict(strs_split[0]) && 
        ft_isdigit_strict(strs_split[1]) && 
        ft_isdigit_strict(strs_split[2]))
    {
        color->R = ft_atoi(strs_split[0]);
        color->G = ft_atoi(strs_split[1]);
        color->B = ft_atoi(strs_split[2]);
    }
    else
    {
        printf(RED"Error\n Invalid color format.\n"RESET);
        exit(EXIT_FAILURE);
    }
}



void parse_color(const char *str, t_color *color)
{
    char **strs_split;

    init_color(color);
    empty_color((char*)str);
  
    strs_split = ft_split(str, ',');
    if (strs_split == NULL)
    {
        ft_error_msg("Error: could not split color components.");
	    free_strs_array(strs_split);
    }
    color_split(strs_split, color);
	free_strs_array(strs_split);
}