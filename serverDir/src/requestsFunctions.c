#include "../includes/serverCS.h"

void		magicValueError(t_cs *cs)
{
	cs->header.length = 0;
	cs->header.requestCode = WRONGMAGICVALUE_RQ;
	sendHeaderServer(cs);
}

void		lengthError(t_cs *cs)
{
	cs->header.length = 0;
	cs->header.requestCode = WRONGLENGHT_RQ;
	sendHeaderServer(cs);
}

void		requestCodeError(t_cs *cs)
{
	cs->header.length = 0;
	cs->header.requestCode = WRONGREQUESCODE_RQ;
	sendHeaderServer(cs);
}

void		getPing(t_cs *cs)
{
	cs->header.length = 0;
	cs->header.requestCode = OK_RQ;
	sendHeaderServer(cs);
}

void		resetStats(t_cs *cs)
{
	cs->header.requestCode = OK_RQ;
	cs->stats = (t_stats){0, 0, 0};
	sendHeaderServer(cs);
}

void		sendHeaderServer(t_cs *cs)
{
	int		checkNum;

	checkNum = (int)send(cs->sockfd, &cs->header.magic_value, sizeof(cs->header.magic_value), 0);
	if (checkNum == -1)
		perror("Problem with sending information to the socket!\n");
	else
		cs->stats.bytesSent += checkNum;

	checkNum = (int)send(cs->sockfd, &cs->header.length, sizeof(cs->header.length), 0);
	if (checkNum == -1)
		perror("Problem with sending information to the socket!\n");
	else
		cs->stats.bytesSent += checkNum;

	checkNum = (int)send(cs->sockfd, &cs->header.requestCode, sizeof(cs->header.requestCode), 0);
	if (checkNum == -1)
		perror("Problem with sending information to the socket!\n");
	else
		cs->stats.bytesSent += checkNum;
}

void		getStatsServer(t_cs *cs)
{
	int		checkNum;

	cs->header.requestCode = OK_RQ;
	sendHeaderServer(cs);

	checkNum = (int)send(cs->sockfd, &cs->stats.bytesReceived, sizeof(cs->stats.bytesReceived), 0);
	if (checkNum == -1)
		perror("Problem with sending information to the socket!\n");
	else
		cs->stats.bytesSent += checkNum;
	
	checkNum = (int)send(cs->sockfd, &cs->stats.compressionRate, sizeof(cs->stats.compressionRate), 0);
	if (checkNum == -1)
		perror("Problem with sending information to the socket!\n");
	else
		cs->stats.bytesSent += checkNum;
	
	cs->stats.bytesSent += sizeof(cs->stats.bytesSent);
	checkNum = (int)send(cs->sockfd, &cs->stats.bytesSent, sizeof(cs->stats.bytesSent), 0);
	if (checkNum == -1)
	{
		cs->stats.bytesSent -= sizeof(cs->stats.bytesSent);
		perror("Problem with sending information to the socket!\n");
	}
}
