#include "../includes/serverCS.h"

int				countChars(const char *str, char c)
{
	int     	counter;

	counter = 0;
	if (!str || !(*str))
		return (0);
	while (str[counter] && str[counter] == c)
		counter++;
	return (counter);
}

int				checkStr(char *str, char **buffer, short *requestCode)
{
	if (!str || !(*str))
		return (1);
	while (*str >= 'a' && *str <= 'z')
		str++;
	if (!*str || *str == '\n')
		return (0);
	else if (ft_isdigit(*str))
	{
		*buffer = strdup("<invalid: contains numbers>");
		*requestCode = CONTAINS_NUMBERS;
	}
	else if (ft_isupper(*str))
	{
		*buffer = strdup("<invalid: contains uppercase characters>");
		*requestCode = CONTAINS_UPPER;
	}
	else
	{
		*buffer = strdup("<invalid: contains bad characters>");
		*requestCode = CONTAINS_BAD_CHARS;
	}
	return (1);
}

char			*algCompresss(char *str, short *requestCode)
{
	char		temp;
	int			numOfChars;
	char		*buffer;
	char		*tempNum;

	if (checkStr(str, &buffer, requestCode) == 1)
		return (buffer);
	buffer = ft_strnew(strlen(str));
	while (*str)
	{
		temp = *str;
		numOfChars = countChars(str, *str);
		if (numOfChars > 2)
		{
			tempNum = ft_itoa(numOfChars);
			strncat(tempNum, str, 1);
			strcat(buffer, tempNum);
			str += numOfChars;
			ft_strdel(&tempNum);
		}
		else
		{
			while (*str && *str == temp)
			{
				if (*str != '\n')
					strncat(buffer, str, 1);
				str++;
			}
		}
	}
	strcat(buffer, "\0");
	return (buffer);
}

void			getCompresssInfo(t_cs *cs, char *str, char *temp)
{
	cs->beforeCompress += strlen(str) * sizeof(str);
	cs->afterCompress += strlen(temp) * sizeof(temp);
	cs->stats.compressionRate = COMPRESSION_RATE(cs->afterCompress, cs->beforeCompress);
}

void			compress(t_cs *cs, char *str)
{
	int			checkNum;
	char		*buffer;
	
	if (!str || strlen(str) > BUFFER_SIZE)
	{
		lengthError(cs);
		return ;
	}
	cs->header.requestCode = OK_RQ;
	if (*str == '\0')
	{
		cs->header.length = 0;
		sendHeaderServer(cs);
		return ;
	}
	buffer = algCompresss(str, &cs->header.requestCode);
	getCompresssInfo(cs, str, buffer);
	if (buffer)
		cs->header.length = (short)strlen(buffer);
	else
		cs->header.length = 0;
	sendHeaderServer(cs);
	checkNum = sendAll(cs->sockfd, buffer, cs->header.length, 0);
	if (checkNum == -1)
		perror("Problem with sending information to the socket!\n");
	else
		cs->stats.bytesSent += checkNum;
	ft_strdel(&buffer);
}
