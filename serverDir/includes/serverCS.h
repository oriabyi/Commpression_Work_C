#ifndef WORK_HEADERSERVER_H
#define WORK_HEADERSERVER_H

#include "../../generalDir/includes/generalCS.h"

/*
 *			QUEUE defines the maximum length to which the queue of pending connections for sockfd may grow.
 */

# define	QUEUE				5
# define	BUFFER_SIZE			32767

/*
 *		 	Response status codes.
 */

# define	OK_RQ				0
# define	WRONGLENGHT_RQ		2
# define	WRONGREQUESCODE_RQ	3
# define	WRONGMAGICVALUE_RQ	33
# define	CONTAINS_NUMBERS	34
# define	CONTAINS_UPPER		35
# define	CONTAINS_BAD_CHARS	36

/*
 *			Formula for calculating compression rate.
 */

# define	COMPRESSION_RATE(x, y) (uint8_t)(100 * ((double)x / (double)y))

/*
 *			Work with client.
 */
void		*doprocessing(void *newcs);

/*
 *			Work with requests.
 */
void		getPing(t_cs *cs);
void		resetStats(t_cs *cs);
void		getStatsServer(t_cs *cs);
void 		compress(t_cs *cs, char *str);

/*
 *			Handle elements of header.
 */
void		lengthError(t_cs *cs);
void		magicValueError(t_cs *cs);
void		requestCodeError(t_cs *cs);

/*
 *			Function to turn letters into numbers.
 */
char		*ft_itoa(int number);

/*
 *			Header submission function.
 */
void		sendHeaderServer(t_cs *cs);

#endif
