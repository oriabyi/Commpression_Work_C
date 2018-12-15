#include "../includes/clientCS.h"

void		getHeader(int sockfd, t_header *header)
{
	*header = (t_header){0, 0, 0};

	recvHandleError(sockfd, &header->magic_value, sizeof(header->magic_value), 0);
	recvHandleError(sockfd, &header->length, sizeof(header->length), 0);
	recvHandleError(sockfd, &header->requestCode, sizeof(header->requestCode), 0);
}

void		getStats(int sockfd, t_stats *stats)
{
	*stats = (t_stats){0, 0, 0};

	recvHandleError(sockfd, &stats->bytesReceived, sizeof(stats->bytesReceived), 0);
	recvHandleError(sockfd, &stats->compressionRate, sizeof(stats->compressionRate), 0);
	recvHandleError(sockfd, &stats->bytesSent, sizeof(stats->bytesSent), 0);
}

void		sendHeaderClient(int sockfd, t_header *header)
{
	sendHandleError(sockfd, &header->magic_value, sizeof(header->magic_value), 0);
	sendHandleError(sockfd, &header->length, sizeof(header->length), 0);
	sendHandleError(sockfd, &header->requestCode, sizeof(header->requestCode), 0);
}
