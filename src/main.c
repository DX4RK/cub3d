/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:29:53 by noldiane          #+#    #+#             */
/*   Updated: 2025/01/16 00:21:34 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_parsing(t_parsing *parsing_info)
{
	parsing_info->fd = -1;
	parsing_info->map = NULL;
	parsing_info->F_COLOR = -1;
	parsing_info->C_COLOR = -1;
	parsing_info->red = -1;
	parsing_info->green = -1;
	parsing_info->blue = -1;
	parsing_info->color_info_ok = -1;
	parsing_info->NO_TEXTURE = NULL;
	parsing_info->SO_TEXTURE = NULL;
	parsing_info->WE_TEXTURE = NULL;
	parsing_info->EA_TEXTURE = NULL;
	parsing_info->texter_info_ok = -1;
	parsing_info->player_set = -1;
	parsing_info->player_x = -1;
	parsing_info->player_y = -1;
	parsing_info->error_code = OK;
}

int	parse_arguments(int argc, char **argv, t_parsing *parsing_info)
{
	int		file_lenght;
	char	*file_format;
	
	if (argc != 2)
	{
		print_error(ERROR_MISSING_CUB);
		return (1);
	}
	file_lenght = ft_strlen(argv[1]);
	file_format = ft_substr(argv[1], (file_lenght -4), 4);
	if (!file_format)
	{
		//print_error malloc
		return (1);
	}
	if (ft_strncmp(file_format, ".cub", 4) != 0)
	{
		free(file_format);
		print_error(ERROR_WRONG_FORMAT);
		return (1);
	}
	if (file_lenght < 5)
	{
		free(file_format);
		//print_error only extension but not a card name
		return (1);
	}
	free(file_format);
	parsing_info->fd = open(argv[1], O_RDONLY);
	if (read(parsing_info->fd, 0, 0) != 0)//vérif si prend en compte erreur si dossier au lieu de fichier
	{
		print_error(FILE_NOT_EXIST);
		return (1);
	}
	return (0);
}

int	empty_line_spaces(char *line, t_parsing *parsing_info)
{
	int	i;
	int	other_than_space;
	int	space;

	i = 0;
	other_than_space = 0;
	space = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			space++;
		else if (line[i] != '\n')
			other_than_space++;
		i++;
	}
	if (space > 0 && other_than_space == 0)//que des espaces donc erreur
	{
		parsing_info->error_code = L_O_S;
		free(line);
		return (1);
	}
	if (space == 0 && other_than_space == 0)//ligne vide
	{
		free(line);
		return (1);
	}
	return (0);
}

/*
int	check_invalide_characters(char *line, t_parsing *parsing_info)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1] != '\0')//normalement jamais le cas si gnl bien fait
			parsing_info->error_code = I_C;
		if (line[i] == ' ')
		{
			i++;
			continue ;
		}
		if (line[i] != 'N' ||)
		i++;
	}
	if (parsing_info->error_code == I_C)
	{
		free(line);
		return (1);
	}
	return (0);
}
*/

/*
int	input_f_color(char *line, t_parsing *parsing_info, int i)
{
	int	r;
	int	g;
	int	b;
	int	s;
	int	in_color_nb;//si est en train de reconstituer le rouge ou le vert ou le bleu

	r = 0;
	g = 0;
	b = 0;
	s = 1;
	in_color_nb = 1;
	while (line[i])
	{
		if (line[i] == ' ')
			while (line[i] == ' ')
			{
				i++;
			}
		else if (line[i] == '+' || line[i] == '-')
		{
			if (line[i] == '-')
				s = -1;
			i++;
		}
		else if (line[i] >= '0' && line[i] <= '9')
		{
			while (line[i] >= '0' && line[i] <= '9')
			{
				if (in_color_nb == 1)
				{
					r = r * 10 + (line[i] - '0');
				}
				if (in_color_nb == 2)
				{
					g = g * 10 + (line[i] - '0');
				}
				if (in_color_nb == 3)
				{
					b = b * 10 + (line[i] - '0');
				}
			}
		}
		ICI
	}
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free(line);
		parsing_info->error_code = M_C_I_M;
		return (1);
	}
	return (0);
}
*/

void	skip_spaces(const char *line, int *i)
{
	while (line[*i] == ' ') //|| (line[*i] >= 9 && line[*i] <= 13))//si on gère les tab etc
		(*i)++;
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (YES);
	return (NO);
}

int	parse_color_value(char *line, t_parsing *parsing_info, int *i)
{
	int	sign;
	int	color_value;
	int	len;

	sign = 1;
	color_value = -1;
	if (line[*i] == '+' || line[*i] == '-')
	{
		if (line[*i] == '-')
			sign = -1;
		(*i)++;
	}
	len = 0;
	if (ft_isdigit(line[*i]))
		color_value = 0;
	while (ft_isdigit(line[*i]))
	{
		color_value = color_value * 10 + (line[*i] - '0');
		(*i)++;
		len++;
		if (color_value > 255 || len > 3 || sign == -1 || len == 0)
		{
			parsing_info->error_code = M_C_I_M;
			return (-1);
		}
	}
	return (color_value);//mettre à 0 et attribuer la valeur de la couleur
}

int rgb_to_int(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int	save_color(t_parsing *parsing_info, int color_type)
{
	if (parsing_info->red == -1 || parsing_info->green == -1 || parsing_info->blue == -1)
	{
		parsing_info->error_code = M_C_I_M;
		return (1);
	}
	if (color_type == F)
		parsing_info->F_COLOR = rgb_to_int(parsing_info->red, parsing_info->green, parsing_info->blue);
	if (color_type == C)
		parsing_info->C_COLOR = rgb_to_int(parsing_info->red, parsing_info->green, parsing_info->blue);
	//normalement pas besoin de remettre à 0
	parsing_info->red = -1;
	parsing_info->green = -1;
	parsing_info->blue = -1;
	return (0);
}

int	input_color(char *line, t_parsing *parsing_info, int i, int color_type)
{
	skip_spaces(line, &i);
	parsing_info->red = parse_color_value(line, parsing_info, &i);
	skip_spaces(line, &i);
	if (line[i] != ',')
		parsing_info->error_code = M_C_I_M;
	i++;
	skip_spaces(line, &i);
	parsing_info->green = parse_color_value(line, parsing_info, &i);
	skip_spaces(line, &i);
	if (line[i] != ',')
		parsing_info->error_code = M_C_I_M;
	i++;
	skip_spaces(line, &i);
	parsing_info->blue = parse_color_value(line, parsing_info, &i);
	skip_spaces(line, &i);
	if (line[i] != '\0' && line[i] != '\n')
		parsing_info->error_code = M_C_I_M;//erreur au niveau de min 1 des lignes couleur ou alors min 1 ligne manquante
	if (save_color(parsing_info, color_type) == 1)
		return (1);
	return (0);
	//vérifier si r g ou b -1 et si oui erreur. Sinon envoie en hex convertisseur et ensuite en fct du paramètre color_type enregistre dans structure la couleur dans f_color ou c_color
}

int	verif_color(char *line, t_parsing *parsing_info, int color_type)
{
	int	temp;

	if (color_type == F)
		temp = parsing_info->F_COLOR;
	else if (color_type == C)
		temp = parsing_info->C_COLOR;
	if (temp != -1)
	{
		parsing_info->error_code = M_C_I_M;
		free(line);
		line = NULL;//pas besoin normalement voir potentiellement une erreur
		return (1);
	}
	if (input_color(line, parsing_info, 1, color_type) == 1)
	{
		free(line);
		line = NULL;//pas besoin normalement
		return (1);
	}
	else//pas besoin normalement, peut mettre contenu sans la structure else
	{
		//cela signifie que que la couleur n'était pas encore attribuée et que l'attribution de la couleur n'a pas occasionné d'erreur.
		//la ligne ne doit pas être free
		free(line);
		line = NULL;//pas besoin normalement
		if (parsing_info->C_COLOR != -1 && parsing_info->F_COLOR != -1)
			parsing_info->color_info_ok = 1;
	}
	return (0);
}

char	*extract_texture_path(char *line, int *i)
{
    int		start;
    int		len;
    char	*path;

    skip_spaces(line, i);
    start = *i;
    while (line[*i] && line[*i] != ' ' && line[*i] != '\n')
        (*i)++;
    len = *i - start;
    if (len <= 0)
        return (NULL);//que espaces ou vide
    path = (char *)malloc(sizeof(char) * (len + 1));
    if (!path)
	{
		//printf("Malloc failed extract texture\n");
		return (NULL);
	}
    ft_strlcpy(path, &line[start], len + 1);
    return (path);
}

int	check_texture_file_valid(char *path)
{
    int	fd;
    int	return_value;

    fd = open(path, O_RDONLY);//fichier inexistant
    if (fd < 0)
    {
        return (1);
    }
    return_value = read(fd, 0, 0);
    if (return_value < 0)//verif si dossier ou fichier
    {
        close(fd);
        return (1);
    }
    close(fd);
    return (0);
}

int	check_xpm_extension(const char *path)
{
    int	len;

    if (!path)
        return (1);
    len = ft_strlen(path);
    if (len < 5)//.xpm mais min 1 char devant
        return (1);
    if (ft_strncmp(path + (len - 4), ".xpm", 4) != 0)
        return (1);
    return (0);
}

int	verif_texture(char *line, t_parsing *parsing_info, int texture_type)
{
    int		i;
    char	*path;

    i = 2;
    if ((texture_type == NO && parsing_info->NO_TEXTURE != NULL)
     || (texture_type == SO && parsing_info->SO_TEXTURE != NULL)
     || (texture_type == WE && parsing_info->WE_TEXTURE != NULL)
     || (texture_type == EA && parsing_info->EA_TEXTURE != NULL))
    {
        parsing_info->error_code = M_T_I_M;
        free(line);
        return (1);
    }
    path = extract_texture_path(line, &i);
    if (!path)
    {
        // Chemin vide ou malloc fail --> envoie struct pour verif l'erreur en detail
        parsing_info->error_code = M_T_I_M;
        free(line);
        return (1);
    }

	if (check_xpm_extension(path) != 0)
    {
        parsing_info->error_code = M_T_I_M;//mauvaise extension
        free(path);
        free(line);
        return (1);
    }

    skip_spaces(line, &i);
    if (line[i] != '\0' && line[i] != '\n')
    {
        // Il y a des caractères en trop --> pas erreur code pour invalide character
        parsing_info->error_code = M_T_I_M;
        free(path);
        free(line);
        return (1);
    }
    if (check_texture_file_valid(path) != 0)
    {
        parsing_info->error_code = M_T_I_M;
        free(path);
        free(line);
        return (1);
    }
    if (texture_type == NO)
        parsing_info->NO_TEXTURE = path;
    else if (texture_type == SO)
        parsing_info->SO_TEXTURE = path;
    else if (texture_type == WE)
        parsing_info->WE_TEXTURE = path;
    else if (texture_type == EA)
        parsing_info->EA_TEXTURE = path;
    if (parsing_info->NO_TEXTURE && parsing_info->SO_TEXTURE
        && parsing_info->WE_TEXTURE && parsing_info->EA_TEXTURE)
    {
        parsing_info->texter_info_ok = 1;
    }
    free(line);
    return (0);
}

int	input_data__NOT_MAP(char *line, t_parsing *parsing_info)
{
	//il y a au min 1 charactère autre que espace ou \n + un \0 donc normalement peut vérifier line[0] et line[1] sans risque car existe
	if (line[0] == 'F' && line[1] == ' ')
	{
		if (verif_color(line, parsing_info, F) == 1)
			return (1);
		return (0);
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		if (verif_color(line, parsing_info, C) == 1)
			return (1);
		return (0);
	}
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
	{
		if (verif_texture(line, parsing_info, NO) == 1)
			return (1);
		return (0);
	}
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
	{
		if (verif_texture(line, parsing_info, SO) == 1)
			return (1);
		return (0);
	}
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
	{
		if (verif_texture(line, parsing_info, WE) == 1)
			return (1);
		return (0);
	}
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
	{
		if (verif_texture(line, parsing_info, EA) == 1)
			return (1);
		return (0);
	}
	else
	{
		//soit invalide charactère soit début de la map alors que pas encore toutes les infos remplis
		parsing_info->error_code = I_C;
		//même si debut de la map sans les infos prédédentes renseignés, c'est un charactère invalide puisque ne doit pas encore commencer par la map
		return (1);
	}
	return (0);
}

int	line_is_empty(char *line)
{
    int	i;

	i = 0;
    if (!line)
        return (1);
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

int	add_map_line(t_parsing *parsing_info, char *str)
{
	int		i;
    int		count;
    char	**new_map;

    count = 0;
    if (parsing_info->map)
    {
        while (parsing_info->map[count])
            count++;
    }
    new_map = malloc(sizeof(char *) * (count + 1 + 1));
    if (!new_map)
    {
		//error
		return (1);
	}
	i = 0;
	while (i < count)
	{
		new_map[i] = parsing_info->map[i];
		i++;
	}
    new_map[count] = ft_strdup(str);
    if (!new_map[count])
    {
		//malloc error handeled in strdup ?
        free(new_map);
        return (1);
    }
    new_map[count + 1] = NULL;
    if (parsing_info->map)
        free(parsing_info->map);
    parsing_info->map = new_map;
    return (0);
}

int	check_map_line(char *line, t_parsing *parsing_info, int y)
{
    int i;

    i = 0;
    while (line[i] && line[i] != '\n')
    {
        //if (line[i] == ' ' || line[i] == '1' || line[i] == '0')
        //{
            // ok
        //}//else if 
        if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
        {
            if (parsing_info->player_set != -1)
            {
                parsing_info->error_code = P_A_S;
                return (1);
            }
            parsing_info->player_set = 1;
            parsing_info->player_y = y;
            parsing_info->player_x = i;
        }
        else if (line[i] != ' ' && line[i] != '1' && line[i] != '0')
        {
            parsing_info->error_code = I_C; 
            return (1);
        }
        i++;
    }
    return (0);
}

int	test_end_map_lines(t_parsing *parsing_info)
{
    char	*line;

    while ((line = get_next_line(parsing_info->fd, 0)) != NULL)
    {
        if (!line_is_empty(line))
        {
            parsing_info->error_code = M_N_C;
            free(line);
            return (1);
        }
        free(line);
    }
    return (0);
}

int	fill_map_parsing_info(t_parsing *parsing_info)
{
    char	*line;
    int		started_map;
    int		ended_map;
    int		map_line_index;//y

    started_map = 0;
    ended_map = 0;
    map_line_index = 0;
    while ((line = get_next_line(parsing_info->fd, 0)) != NULL && parsing_info->error_code == OK)
    {
        if (line_is_empty(line))
        {
            free(line);
            if (!started_map)
            {
                continue;
            }
            else //fin de map ligne vide
            {
                ended_map = 1;
                if (test_end_map_lines(parsing_info) == 1)
                    return (1);
                break;
            }
        }
        else
        {
            if (ended_map)//blabla après fin de carte mais dc carte ouverte pas fermée
            {
                parsing_info->error_code = M_N_C; 
                free(line);
                return (1);
            }
            started_map = 1;
            if (check_map_line(line, parsing_info, map_line_index) == 1)
            {
                free(line);
                return (1);
            }
            if (add_map_line(parsing_info, line) == 1)
            {
                //malloc error
                free(line);
                return (1);
            }
            free(line);
            map_line_index++;
        }
    }
    if (started_map == 0)
    {
        parsing_info->error_code = E_M;
        return (1);
    }
    if (parsing_info->player_set != 1)
    {
        parsing_info->error_code = P_N_S;
        return (1);
    }
    return (0);
}

int	fill_config_parsing_info(t_parsing *parsing_info)
{
	char	*line;

	while ((line = get_next_line(parsing_info->fd, 0)) != NULL && parsing_info->error_code == OK)//0 dans gnl ????
	{
		//if (empty_line_spaces(line, parsing_info) == 1)
		//	continue ;
		//if (check_invalide_characters(line, parsing_info) == 1)
		//	return (1);
		//clean \n fct
		if (parsing_info->color_info_ok != 1 || parsing_info->texter_info_ok != 1)
		{
			if (empty_line_spaces(line, parsing_info) == 1)
				continue ;
			//s'occupe de parser la ligne dans cette fonction la
			if (input_data__NOT_MAP(line, parsing_info) == 1)
				return (1);
		}
		if (parsing_info->color_info_ok == 1 && parsing_info->texter_info_ok == 1)
			return (0);
		//else signifie que plus que data map donc erreur pour tout charactère ne constituant pas la map
		//il peut y avoir des sauts de lignes vides avant la map et après mais pas pendant
		//toutefois, après la map, les lignes remplis d'espaces ne doivent pas compter comme erreur
		
		//else
		//	return 0 car lance autre bloc de lecture de la map et pas des données de config
		//non pas de else car sinon ne prend pas en compte le traitement actuel de la ligne donc si la ligne permet d'avoir le dernier truc config et mets ensuite les deux vérifications à 1 alors ne rentre pas dans le else mais autrement si.
	}
	return (0);
}




int check_player_rules(t_parsing *parsing_info,
    int y, int x, int rows_count, int line_len)
{
	char	*valid_neighbors;
    if (y == 0 || y == rows_count - 1
        || x == 0 || x == line_len - 1)
    {
        parsing_info->error_code = M_C_I_M;// a revoir
        return (1);
    }
    valid_neighbors = "10NSEW";
    if (check_neighbor(parsing_info, y - 1, x, rows_count, line_len, valid_neighbors))
        return (1);
    if (check_neighbor(parsing_info, y + 1, x, rows_count, line_len, valid_neighbors))
        return (1);
    if (check_neighbor(parsing_info, y, x - 1, rows_count, line_len, valid_neighbors))
        return (1);
    if (check_neighbor(parsing_info, y, x + 1, rows_count, line_len, valid_neighbors))
        return (1);
    return (0);
}

int	check_floor_rules(t_parsing *parsing_info,
    int y, int x, int rows_count, int line_len)
{
	char	*valid_neighbors;
    if (y == 0 || y == rows_count - 1
        || x == 0 || x == line_len - 1)
    {
        parsing_info->error_code = M_C_I_M;// a revoir
        return (1);
    }
    valid_neighbors = "10NSEW";
    if (check_neighbor(parsing_info, y - 1, x, rows_count, line_len, valid_neighbors))
        return (1);
    if (check_neighbor(parsing_info, y + 1, x, rows_count, line_len, valid_neighbors))
        return (1);
    if (check_neighbor(parsing_info, y, x - 1, rows_count, line_len, valid_neighbors))
        return (1);
    if (check_neighbor(parsing_info, y, x + 1, rows_count, line_len, valid_neighbors))
        return (1);
    return (0);
}

int check_space_rules(t_parsing *parsing_info,
    int y, int x, int rows_count, int line_len)
{
    char	*valid_neighbors;

	valid_neighbors = " 1";
    if (check_neighbor(parsing_info, y - 1, x, rows_count, line_len, valid_neighbors) == 1)
        return (1);
    if (check_neighbor(parsing_info, y + 1, x, rows_count, line_len, valid_neighbors) == 1)
        return (1);
    if (check_neighbor(parsing_info, y, x - 1, rows_count, line_len, valid_neighbors) == 1)
        return (1);
    if (check_neighbor(parsing_info, y, x + 1, rows_count, line_len, valid_neighbors) == 1)
        return (1);
    return (0);
}

int	verify_cell_and_neighbors(t_parsing *parsing_info,
    int y, int x, int rows_count, int line_len)
{
    char	c;

    c = parsing_info->map[y][x];
    if (c == ' ')
        return check_space_rules(parsing_info, y, x, rows_count, line_len);
    //else if (c == '1')
    //    return check_wall_rules(parsing_info, y, x, rows_count, line_len);
	//peut faire ce que veut avec 1
    else if (c == '0')
        return check_floor_rules(parsing_info, y, x, rows_count, line_len);
    else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return check_player_rules(parsing_info, y, x, rows_count, line_len);
    return (0);
}

int	check_map_line_valid(t_parsing *parsing_info, int y, int rows_count)
{
    int		x;
    char	*line;
    int		line_len;

    line = parsing_info->map[y];
    if (!line)
        return (0);//inutile normalement
    line_len = ft_strlen__SANS_N(line);
    x = 0;
    while (x < line_len)
    {
        if (verify_cell_and_neighbors(parsing_info, y, x, rows_count, line_len) == 1)
            return (1);
        x++;
    }
    return (0);
}

int	check_map_valid(t_parsing *parsing_info)
{
    int	y;
    int	rows_count;

    y = 0;
    rows_count = 0;
    while (parsing_info->map && parsing_info->map[rows_count])
        rows_count++;
    while (y < rows_count)
    {
        if (check_map_line_valid(parsing_info, y, rows_count) == 1)
            return (1);
        y++;
    }
    return (0);
}






int	parsing(int argc, char **argv, t_parsing *parsing_info)
{
	//il faut également penser à print les erreurs car dans fonctions il me semble que attribue uniquement l'erreur rencontrée
	init_parsing(parsing_info);
	if (parse_arguments(argc, argv, parsing_info) == 1)
		return (1);//pas de changement du error code fait
	if (fill_config_parsing_info(parsing_info) == 1)
		return (1);
	if (fill_map_parsing_info(parsing_info) == 1)
		return (1);
	//check map fermée et valide (espaces)
	
	//remplire structures noldiane avec les données de ma structure
	return (0);
}

/*
il faut vérifier le charactère à gauche et à droite ainsi que au dessus et en dessous (attention à ne pas out of exception error si le premier ou le dernier élement dans la ligne (sachant qu'une ligne se termine soit par \n ou \0) ainsi que si on se trouve dans la première colonne ou la dernière)
les espaces ont le droit d'etre uniquement a coté de 1 et d'autres espaces sinon erreur
les 1 peuvent être à coté de tout mais doivent être au moins à coté d'un autre 1, 0, N, S, E, W sinon erreur
les 0 peuvent etre a coté d'autres 0, de N, S, E, W et de 1 sinon erreur
les N, S, E, W peuvent etre a coté de 0 et de 1, sinon erreur
les N, S, E, W et 0 n'ont pas le droit d'être le premier element ou le dernier d'une ligne (une ligne se termine par \n ou \0) sinon erreur. 
les N, S, E, W et 0 n'ont pas le droit d'être dans la premiere ou la dernière ligne

*/

//ne gère pas toutes les erreurs comme des ilots de 1 entre des espaces

int	main(int argc, char *argv[])
{
//	t_game		*game;
	t_parsing	parsing_info;
	//int			fd;

	print_title();
	/**/
//	game = NULL;
	//parsing_info = NULL;
	if (parsing(argc, argv, &parsing_info) != 0)
	{
		//free parsing_info structure data si jamais elles ont été malloc ce qui n'est pas forcement le cas
		//si fd open alors doit le close ??
		return (1);
	}
	/**/

	//fd = parse_arguments(argc, argv);

//	init_game(fd, &game);
//	init_hooks(game);

	//draw_square(WIN_WIDTH / 2, WIN_HEIGHT / 2, 10, 0x00FF00, game);
//	print_keys();
//	mlx_loop(game->mlx_pointer);
	//close fd + free tout ce qu'il y a a free
	return (0);
}
