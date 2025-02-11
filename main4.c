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



/**/

size_t	ft_strlen(const char *str)
{
	size_t	index;

	index = 0;
	while (str[index] != '\0')
	{
		index++;
	}
	return (index);
}

char	*ft_strdup(const char *str)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!ptr)
	{
		return (NULL);
	}
	while (str[i] != '\0')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	if (!s)
	{
		return (NULL);
	}
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (i < len && s[start + i])
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		i++;
	}
	if (i < n)
	{
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}
	return (0);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t destSize)
{
	size_t	index;

	index = 0;
	if (destSize > 0)
	{
		while (src[index] && index < (destSize - 1))
		{
			dest[index] = src[index];
			index++;
		}
		dest[index] = '\0';
	}
	while (src[index])
	{
		index++;
	}
	return (index);
}






char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc(((s1_len + s2_len) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (i < s1_len && s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len && s2[i])
	{
		ptr[s1_len + i] = s2[i];
		i++;
	}
	ptr[s1_len + i] = '\0';
	return (ptr);
}

void	*ft_memset(void *str, int rp, size_t n)
{
	size_t	counter;

	counter = 0;
	while (counter != n)
	{
		*(unsigned char *)(str + counter) = (unsigned char)rp;
		counter++;
	}
	return (str);
}


void	*ft_bzero(void *str, size_t n)
{
	ft_memset(str, '\0', n);
	return (str);
}


void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(nitems * size);
	if (!ptr)
	{
		return (NULL);
	}
	ft_bzero(ptr, nitems * size);
	return (ptr);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	c = (char)c;
	while (str[i] != '\0' || (c == '\0' && str[i] == '\0'))
	{
		if (str[i] == c)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}


void reset_buffer(char **buffer)
{
	printf("Received buffer: %p\n", (void*)*buffer);  // Debug print
	if (buffer && *buffer)
	{
		printf("free\n");
		free(*buffer);
		*buffer = NULL;
	}
}

char	*add_buffer(char *stash, char *buffer)
{
	char	*new_stash;

	new_stash = ft_strjoin(stash, buffer);
	free(stash);
	return (new_stash);
}

char	*read_file(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;

	if (!stash)
		stash = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		stash = add_buffer(stash, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (stash);
}

char	*extract_line(char *buffer)
{
	char	*line;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!buffer[len])
		return (NULL);
	while (buffer[len] && buffer[len] != '\n')
		len++;
	line = ft_calloc(len + 2, sizeof(char));
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*next_line(char *buffer)
{
	char	*line;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (!buffer[len])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc(ft_strlen(buffer) - len + 1, sizeof(char));
	len++;
	while (buffer[len])
		line[i++] = buffer[len++];
	free(buffer);
	return (line);
}

char	*get_next_line(int fd, int t)
{
	char			*line;
	static char		*buffer;

	if (t == 3)
	{
		reset_buffer(&buffer);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = next_line(buffer);
	
	return (line);
}

/**/

void print_error(char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
}











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
	parsing_info->map_height = 0;
}

int	parse_arguments(int argc, char **argv, t_parsing *parsing_info)
{
	int		file_lenght;
	char	*file_format;
	
	if (argc != 2)
	{
		print_error(ERROR_MISSING_CUB);
		printf("\n");
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
		printf("\n");
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
	if (space > 0 && other_than_space == 0)
	{
		parsing_info->error_code = L_O_S;
		free(line);
		return (1);
	}
	if (space == 0 && other_than_space == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

void	skip_spaces(const char *line, int *i)
{
	while (line[*i] == ' ')
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
	return (color_value);
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
		parsing_info->error_code = M_C_I_M;
	if (save_color(parsing_info, color_type) == 1)
		return (1);
	return (0);
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
		line = NULL;
		return (1);
	}
	if (input_color(line, parsing_info, 1, color_type) == 1)
	{
		free(line);
		line = NULL;
		return (1);
	}
	else//pas besoin normalement, peut mettre contenu sans la structure else
	{
		free(line);
		line = NULL;
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
		return (NULL);
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

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		return (1);
	}
	return_value = read(fd, 0, 0);
	if (return_value < 0)
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
	if (len < 5)
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
		parsing_info->error_code = I_C;
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
	int		y;

	started_map = 0;
	ended_map = 0;
	y = 0;
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
			if (check_map_line(line, parsing_info, y) == 1)
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
			y++;
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

	while ((line = get_next_line(parsing_info->fd, 0)) != NULL && parsing_info->error_code == OK)
	{
		if (parsing_info->color_info_ok != 1 || parsing_info->texter_info_ok != 1)
		{
			if (empty_line_spaces(line, parsing_info) == 1)
				continue ;
			if (input_data__NOT_MAP(line, parsing_info) == 1)
				return (1);
		}
		if (parsing_info->color_info_ok == 1 && parsing_info->texter_info_ok == 1)
			return (0);
	}
	return (0);
}

int	ft_strlen__NO_N(const char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0' && str[index] != '\n')
	{
		index++;
	}
	return (index);
}

char	get_neighbor_char(t_parsing *parsing_info, int y, int x,
	int nb_y)
{
	char	*line;

	if (y < 0 || y >= nb_y)
		return (' ');
	line = parsing_info->map[y];
	if (!line)
		return (' ');
	if (x < 0 || x >= ft_strlen__NO_N(line))
		return (' ');
	return (line[x]);
}

int	is_in_set(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_neighbor(t_parsing *parsing_info,
	int y, int x, char *valid_neighbors)
{
	char	neighbor;

	neighbor = get_neighbor_char(parsing_info, y, x, parsing_info->map_height);
	if (!is_in_set(neighbor, valid_neighbors))
	{
		parsing_info->error_code = M_N_C;
		return (1);
	}
	return (0);
}

int check_player_rules(t_parsing *parsing_info,
	int y, int x, int line_len)
{
	char	*valid_neighbors;
	if (y == 0 || y == parsing_info->map_height - 1
		|| x == 0 || x == line_len - 1)
	{
		parsing_info->error_code = M_N_C;
		return (1);
	}
	valid_neighbors = "10NSEW";
	if (check_neighbor(parsing_info, y - 1, x, valid_neighbors))
		return (1);
	if (check_neighbor(parsing_info, y + 1, x, valid_neighbors))
		return (1);
	if (check_neighbor(parsing_info, y, x - 1, valid_neighbors))
		return (1);
	if (check_neighbor(parsing_info, y, x + 1, valid_neighbors))
		return (1);
	return (0);
}

int	check_floor_rules(t_parsing *parsing_info,
	int y, int x, int line_len)
{
	char	*valid_neighbors;
	if (y == 0 || y == parsing_info->map_height - 1
		|| x == 0 || x == line_len - 1)
	{
		parsing_info->error_code = M_N_C;
		return (1);
	}
	valid_neighbors = "10NSEW";
	if (check_neighbor(parsing_info, y - 1, x, valid_neighbors))
		return (1);
	if (check_neighbor(parsing_info, y + 1, x, valid_neighbors))
		return (1);
	if (check_neighbor(parsing_info, y, x - 1, valid_neighbors))
		return (1);
	if (check_neighbor(parsing_info, y, x + 1, valid_neighbors))
		return (1);
	return (0);
}

int check_space_rules(t_parsing *parsing_info,
	int y, int x)
{
	char	*valid_neighbors;

	valid_neighbors = " 1";
	if (check_neighbor(parsing_info, y - 1, x, valid_neighbors) == 1)
		return (1);
	if (check_neighbor(parsing_info, y + 1, x, valid_neighbors) == 1)
		return (1);
	if (check_neighbor(parsing_info, y, x - 1, valid_neighbors) == 1)
		return (1);
	if (check_neighbor(parsing_info, y, x + 1, valid_neighbors) == 1)
		return (1);
	return (0);
}

int	verify_cell_and_neighbors(t_parsing *parsing_info,
	int y, int x, int line_len)
{
	char	c;

	c = parsing_info->map[y][x];
	if (c == ' ')
		return check_space_rules(parsing_info, y, x);
	else if (c == '0')
		return check_floor_rules(parsing_info, y, x, line_len);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return check_player_rules(parsing_info, y, x, line_len);
	return (0);
}

int	check_map_line_valid(t_parsing *parsing_info, int y, int nb_y)
{
	int		x;
	char	*line;
	int		line_len;

	line = parsing_info->map[y];
	if (!line)
		return (0);
	line_len = ft_strlen__NO_N(line);
	parsing_info->map_height = nb_y;
	x = 0;
	while (x < line_len)
	{
		if (verify_cell_and_neighbors(parsing_info, y, x, line_len) == 1)
			return (1);
		x++;
	}
	return (0);
}

int	check_map_valid(t_parsing *parsing_info)
{
	int	y;
	int	nb_y;

	y = 0;
	nb_y = 0;
	while (parsing_info->map && parsing_info->map[nb_y])
		nb_y++;
	while (y < nb_y)
	{
		if (check_map_line_valid(parsing_info, y, nb_y) == 1)
			return (1);
		y++;
	}
	return (0);
}

int	parsing(int argc, char **argv, t_parsing *parsing_info)
{
	init_parsing(parsing_info);
	if (parse_arguments(argc, argv, parsing_info) == 1)
		return (1);//pas de changement du error code fait
	if (fill_config_parsing_info(parsing_info) == 1)
		return (1);
	if (fill_map_parsing_info(parsing_info) == 1)
		return (1);
	if (check_map_valid(parsing_info) == 1)
		return (1);
	return (0);
}

void print_parsing(t_parsing *p)
{
	if (!p)
	{
		printf("Erreur : structure t_parsing invalide (NULL)\n");
		return;
	}

	printf("===== Données de t_parsing =====\n");

	// Fichier
	printf("fd : %d\n", p->fd);

	// Affichage de la map si elle existe
	if (p->map)
	{
		printf("map :\n");
		for (int i = 0; p->map[i] != NULL; i++)
		{
			int len = ft_strlen(p->map[i]);
			printf("  %s len : %d\n", p->map[i], len);//  \n
		}
	}
	else
	{
		printf("map : NULL\n");
	}

	// Couleurs
	printf("\n");
	printf("F_COLOR : %d\n", p->F_COLOR);
	printf("C_COLOR : %d\n", p->C_COLOR);
	printf("Red : %d\n", p->red);
	printf("Green : %d\n", p->green);
	printf("Blue : %d\n", p->blue);
	printf("color_info_ok : %d\n", p->color_info_ok);

	// Textures
	printf("NO_TEXTURE : %s\n", p->NO_TEXTURE ? p->NO_TEXTURE : "NULL");
	printf("SO_TEXTURE : %s\n", p->SO_TEXTURE ? p->SO_TEXTURE : "NULL");
	printf("WE_TEXTURE : %s\n", p->WE_TEXTURE ? p->WE_TEXTURE : "NULL");
	printf("EA_TEXTURE : %s\n", p->EA_TEXTURE ? p->EA_TEXTURE : "NULL");

	printf("texter_info_ok : %d\n", p->texter_info_ok);

	// Player
	printf("player_set : %d\n", p->player_set);

	// Code erreur
	printf("error_code : %d\n", p->error_code);

	printf("================================\n");
}

int	main(int argc, char *argv[])
{
	t_parsing	parsing_info;

	if (parsing(argc, argv, &parsing_info) != 0)
	{
		//free parsing_info structure data si jamais elles ont été malloc ce qui n'est pas forcement le cas
		//free si jamais remplis la structure de noldiane
		//si fd open alors doit le close ??
		print_parsing(&parsing_info);//debug
		return (1);
	}
	//ou alors remplir la structure de noldiane ici
	print_parsing(&parsing_info);
	return (0);
}
