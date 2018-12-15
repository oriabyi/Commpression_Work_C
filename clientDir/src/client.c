#include "../includes/clientCS.h"

void		checkArguments(int ac, char **av)
{
	if (ac == 0 || av == NULL)
		errorChecking(ERROR, "Client: there is a problem with environment!");
	if (ac != 4)
		errorChecking(ERROR, "Client usage: ./client hostname port request_code\n");
	else if (!(av[2]) || areNumbers(av[2]))
		errorChecking(ERROR, "Client: there is a wrong port\n");
	else if (!(av[3]) || areNumbers(av[3]))
		errorChecking(ERROR, "Client: port has to contain only numbers!\n");
}

void		getSendMessageIf(int sockfd, t_header *header)
{
	int		checkNum;
	char	*buffer;

	if (header->requestCode == COMPRESS)
	{
		printf("Client: Please enter the message: ");
		getAllLines(&buffer);
		header->length = (buffer) ? (short)strlen(buffer) : (short)0;
	}
	sendHeaderClient(sockfd, header);
	if (header->requestCode != COMPRESS)
		return ;
	checkNum = sendAll(sockfd, buffer, header->length, 0);
	errorChecking(checkNum, "Client: ERROR sending\n");
	ft_strdel(&buffer);
}

int						main(int ac, char **av)
{
	t_cs				cs;
	char				*buffer;
	struct hostent		*server;
	struct sockaddr_in	serv_addr;
	int					portno, tempRC;

	checkArguments(ac, av);
	cs.header.magic_value = MAGIC_VALUE;
	
	if (av[3])
		cs.header.requestCode = (short)strtol(av[3], NULL, 10);
	if ((portno = (int)strtol(av[2], NULL, 10)) < 0)
		errorChecking(ERROR, "Client: the port is invalid!");

	cs.sockfd = socketHandleError(AF_INET, SOCK_STREAM, 0);
	if ((server = gethostbyname(av[1])) == NULL)
		errorChecking(ERROR, "Client: ERROR, no such host\n");

	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy(server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	cs.sockfd = connectHandleError(cs.sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	tempRC = cs.header.requestCode;
	
	halt(&cs);
	get_signal();
	getSendMessageIf(cs.sockfd, &cs.header);
	
	getHeader(cs.sockfd, &cs.header);
	
	if (tempRC == GET_STATS)
	{
		getStats(cs.sockfd, &cs.stats);
	}
	else if (tempRC == COMPRESS)
	{
		if (cs.header.length > 0)
		{
			buffer = (char *) malloc((size_t) cs.header.length);
			recvHandleError(cs.sockfd, buffer, (size_t) cs.header.length, 0);
		}
	}
	return (0);
}
