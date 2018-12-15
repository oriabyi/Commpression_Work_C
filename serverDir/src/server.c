#include "../includes/serverCS.h"

void		sackaddrInitialization(struct sockaddr_in *serv_addr, char *str)
{
	int 	tempPort;

	if (areNumbers(str))
		errorChecking(ERROR, "Server: port has to contain only numbers!\n");
	if ((tempPort = (int)strtol(str, NULL, 10)) < 0)
		errorChecking(ERROR, "Server: the port is invalid!");
	bzero((char *)serv_addr, sizeof(serv_addr));

	serv_addr->sin_family = AF_INET;
	serv_addr->sin_addr.s_addr = INADDR_ANY;
	serv_addr->sin_port = htons(tempPort);
}

int			check_header(int sock, t_header *ret, t_stats *stats)
{
	*ret = (t_header){0, 0, 0};
	
	stats->bytesReceived += recvHandleError(sock, &ret->magic_value, sizeof(ret->magic_value), 0);
	if (ret->magic_value != MAGIC_VALUE)
		return (1);

	stats->bytesReceived += recvHandleError(sock, &ret->length, sizeof(ret->length), 0);
	if ((size_t)ret->length > BUFFER_SIZE)
		return (2);

	stats->bytesReceived += recvHandleError(sock, &ret->requestCode, sizeof(ret->requestCode), 0);
	if (ret->requestCode < 1 || ret->requestCode > 4)
		return (3);

	return(0);
}

void		*doprocessing(void *newcs)
{
	int 	errorNum;
	char	buffer[BUFFER_SIZE];
	t_cs	*cs;
	
	cs = (t_cs *)newcs;
	bzero(buffer, BUFFER_SIZE);
	errorNum = check_header(cs->sockfd, &cs->header, &cs->stats);
	if (errorNum)
	{
		if (errorNum == 1)
			magicValueError(cs);
		else if (errorNum == 2)
			lengthError(cs);
		else if (errorNum == 3)
			requestCodeError(cs);
	}
	else if (cs->header.requestCode == PING)
		getPing(cs);
	else if (cs->header.requestCode == GET_STATS)
		getStatsServer(cs);
	else if (cs->header.requestCode == RESET_STATS)
		resetStats(cs);
	else if (cs->header.requestCode == COMPRESS)
	{
		cs->stats.bytesReceived += recvHandleError(cs->sockfd, buffer, (size_t)cs->header.length, 0);
		compress(cs, buffer);
	}
	return (NULL);
}

int			main(int ac, char **av)
{
	t_cs				cs;
	pthread_t			thread;
	struct sockaddr_in	serv_addr;
	int					sockfd;

	if (ac < 2 || !av[1])
		errorChecking(ERROR, "Server usage: ./server port\n");
	cs = (t_cs) {0, 0, 0, {0, 0, 0}, {0, 0, 0}};
	sockfd = socketHandleError(AF_INET, SOCK_STREAM, 0);
	sackaddrInitialization(&serv_addr, av[1]);
	bindHandleError(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	listenHandleError(sockfd, QUEUE);
	while (ac)
	{
		get_signal();
		halt(&cs);
		cs.sockfd = acceptHandleError(sockfd, NULL, NULL);
		pthreadCreateHandleError(&thread, NULL, (void *)doprocessing, &cs);
		pthreadJoinHandleError(thread, NULL);
		pthread_cancel(thread);
		close(cs.sockfd);
	}
	return (0);
}
