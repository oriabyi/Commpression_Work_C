#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <netdb.h>
#include "unistd.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/*
 *						Requests codes for convenience and understanding.
 */

# define PING			1
# define GET_STATS		2
# define RESET_STATS	3
# define COMPRESS		4

# define ERROR			-1
# define MAGIC_VALUE	0x53545259


typedef struct			s_header
{
	int					magic_value;
	short				length;
	short				requestCode;
}						t_header;

typedef struct			s_stats
{
	unsigned int		bytesReceived;
	unsigned int		bytesSent;
	uint8_t				compressionRate;
}						t_stats;

typedef struct			s_compressionService
{
	int 				sockfd;
	int 				beforeCompress;
	int 				afterCompress;
	t_header			header;
	t_stats				stats;
}						t_cs;

/*
 *						All library functions with handling errors.
 */

int						listenHandleError(int sockfd, int backlog);
int 					socketHandleError(int domain, int type, int protocol);
int						pthreadJoinHandleError(pthread_t thread, void **retval);
int						recvHandleError(int sockfd, void *buf, size_t len, int flags);
int						sendHandleError(int sockfd, void *buf, size_t len, int flags);
int 					acceptHandleError(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int 					bindHandleError(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int						connectHandleError(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int						pthreadCreateHandleError(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

/*
 *						Secondary functions
 */

int						areNumbers(char *str);
void					ft_strdel(char **as);
char					*ft_strnew(size_t size);
int						errorChecking(int i, char *message);
int						sendAll(int s, char *buf, int len, int flags);
int 					ft_isdigit(char c);
int 					ft_isupper(char c);

/*
 *						Functions for handling signals (like SIGABRT, SIGTERM, SIGKILL, etc.).
 */

t_cs					*halt(t_cs *t);
void					get_signal(void);

#endif