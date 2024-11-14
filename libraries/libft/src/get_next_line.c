/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:54:31 by nolans            #+#    #+#             */
/*   Updated: 2024/11/08 15:42:44 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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

/*
int	main(int argc, char *argv[])
{
	int	fd;
    int		lines;
	char	*line; 

	printf("BUFFER SIZE: %d\n", BUFFER_SIZE);

	lines = 1;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);

    while ((line = get_next_line(fd)) != NULL) {
        printf("%d-> %s", lines++, line);
    }

    close(fd);
    return 0;
}
*/
