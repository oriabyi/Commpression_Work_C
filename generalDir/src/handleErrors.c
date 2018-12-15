#include "../includes/generalCS.h"

int 		socketHandleError(int domain, int type, int protocol)
{
	int		sockfd;
	
	sockfd = socket(domain, type, protocol);
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
		errorChecking(ERROR, "setsockopt(SO_REUSEADDR) failed");
	if (sockfd < 0)
	{
		perror("ERROR opening socket\n");
		exit (1);
	}
	return (sockfd);
}

int			connectHandleError(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int		checkNum;
	
	checkNum = connect(sockfd, addr, addrlen);
	if (checkNum < 0)
	{
		perror("ERROR connecting\n");
		exit (1);
	}
	return (sockfd);
}

int			bindHandleError(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int 	checkNum;
	
	checkNum = bind(sockfd, addr, addrlen);
	if (checkNum < 0)
	{
		perror("ERROR on binding\n");
		exit (1);
	}
	return (sockfd);
}

int			acceptHandleError(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	sockfd = accept(sockfd, addr, addrlen);
	if (sockfd < 0)
	{
		perror("ERROR on accept\n");
		exit (1);
	}
	return (sockfd);
}

int			recvHandleError(int sockfd, void *buf, size_t len, int flags)
{
	int		checkNum;
	
	checkNum = (int)recv(sockfd, buf, len, flags);
	if (checkNum < 0)
	{
		perror("ERROR reading from socket\n");
		exit (1);
	}
	return (checkNum > 0 ? checkNum : 0);
}

int			sendHandleError(int sockfd, void *buf, size_t len, int flags)
{
	int		checkNum;
	
	checkNum = (int)send(sockfd, buf, len, flags);
	if (checkNum < 0)
	{
		perror("ERROR sending\n");
		exit (1);
	}
	return (checkNum > 0 ? checkNum : 0);
}

int			pthreadCreateHandleError(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg)
{
	int 	checkNum;
	
	checkNum = pthread_create(thread, attr, start_routine, arg);
	if (checkNum)
	{
		perror("ERROR creating thread\n");
		exit (1);
	}
	return (0);
}

int			pthreadJoinHandleError(pthread_t thread, void **retval)
{
	int 	checkNum;
	
	checkNum = pthread_join(thread, retval);
	if (checkNum)
	{
		perror("ERROR joining thread\n");
		exit (1);
	}
	return (0);
}

int			listenHandleError(int sockfd, int backlog)
{
	int 	checkNum;
	
	checkNum = listen(sockfd, backlog);
	if (checkNum < 0)
	{
		perror("ERROR with listening\n");
		exit (1);
	}
	return (0);
}