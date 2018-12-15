#ifndef WORK_HEADERCLIENT_H
#define WORK_HEADERCLIENT_H

#include "../../generalDir/includes/generalCS.h"

/*
 *			LGNLBUF it is a size of buffer in function getAllLines.
 */
# define	LGNLBUF		5

void		sendHeaderClient(int sockfd, t_header *header);

/*
 *			Get Stats/Header which sent by server.
 */
void		getStats(int sockfd, t_stats *stats);
void		getHeader(int sockfd, t_header *header);

/*
 *			Get message from user.
 */
int			getAllLines(char **line);

#endif
