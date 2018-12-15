#include "../includes/clientCS.h"

char			*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char		*dest;
	size_t		counter;

	counter = 0;
	if (!s)
		return (NULL);
	dest = ft_strnew(len);
	while (s[start] && counter < len)
		dest[counter++] = s[start++];
	dest[counter] = '\0';
	return (dest);
}

int				getPosition(const char *s, char c, int pos)
{
	int			counter;

	counter = 0;
	if (!s)
		return (-2);
	while (s[counter] && counter < pos)
	{
		if (s[counter] == c)
			return (counter);
		counter++;
	}
	return (-1);
}

char			*ft_strjoin(char const *str1, char const *str2)
{
	char		*dest;
	int			counter;

	counter = 0;
	if (!str1 && !str2)
		return (NULL);
	if (!(dest = (char*)malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1))))
		return (NULL);
	while (*str1)
		dest[counter++] = *str1++;
	while (*str2)
		dest[counter++] = *str2++;
	dest[counter] = '\0';
	return (dest);
}

int				getAllLines(char **line)
{
	int			pos;
	char		*temp;
	char		*tempBuf;
	char		buf[LGNLBUF];

	bzero(buf, LGNLBUF);
	*line = NULL;
	while (fgets(buf, LGNLBUF, stdin) > 0)
	{
		tempBuf = strdup(buf);
		if (*tempBuf == '\0' || *tempBuf == '\n')
			break ;
		if ((pos = getPosition(tempBuf, '\n', LGNLBUF)) > 0 ||
			(pos = getPosition(tempBuf, '\0', LGNLBUF)) > 0)
		{
			if (!*line)
				*line = ft_strsub(tempBuf, 0, (size_t)(pos));
			else
			{
				temp = ft_strsub(tempBuf, 0, (size_t)(pos));
				ft_strdel(&tempBuf);
				tempBuf = ft_strjoin(*line, temp);
				ft_strdel(line);
				*line = strdup(tempBuf);
				ft_strdel(&temp);
			}
			break ;
		}
		if (!*line)
			*line = strdup(tempBuf);
		else
		{
			temp = ft_strjoin(*line, tempBuf);
			ft_strdel(line);
			*line = strdup(temp);
			ft_strdel(&temp);
		}
		bzero(buf, LGNLBUF);
	}
	return (*line ? (int)strlen(*line) : 0);
}
