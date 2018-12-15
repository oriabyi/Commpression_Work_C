#include "../includes/generalCS.h"

char			*ft_strnew(size_t size)
{
	char		*ret;
	
	if (!(ret = (char *)malloc(sizeof(*ret) * (size + 1))))
		return (NULL);
	return (memset(ret, 0, size + 1));
}

void			ft_strdel(char **as)
{
	if (!as || !*as)
		return ;
	if (*as)
	{
		free(*as);
		*as = NULL;
	}
}

int 			ft_isdigit(char c)
{
	return (c >= '0' && c <= '9' ? 1 : 0);
}

int 			ft_isupper(char c)
{
	return (c >= 'A' && c <= 'Z' ? 1 : 0);
}

int				areNumbers(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

int				sendAll(int s, char *buf, int len, int flags)
{
	int			checkNum;
	int			total;
	
	total = 0;
	checkNum = 0;
	while (total < len)
	{
		checkNum = (int)send(s, buf + total, (size_t)len - total, flags);
		if (checkNum == -1)
			break ;
		total += checkNum;
	}
	return (checkNum == -1 ? -1 : total);
}

int				errorChecking(int i, char *message)
{
	if (i < 0)
	{
		perror(message);
		exit (1);
	}
	return (1);
}

size_t			numLen(int numb)
{
	size_t		lenNumber;
	
	lenNumber = 1;
	if (numb < 0)
		lenNumber++;
	while (numb /= 10)
		lenNumber++;
	return (lenNumber);
}

char			*ft_itoa(int number)
{
	char		*ret;
	ssize_t		ssizetNumber;
	size_t		lenght;
	
	lenght = numLen(number);
	if (!(ret = ft_strnew(lenght)))
		return (NULL);
	ssizetNumber = (ssize_t)number;
	if (ssizetNumber < 0)
	{
		ret[0] = '-';
		ssizetNumber = -ssizetNumber;
	}
	ret[--lenght] = (char)(ssizetNumber % 10 + '0');
	while (ssizetNumber /= 10)
		ret[--lenght] = (char)(ssizetNumber % 10 + '0');
	return (ret);
}