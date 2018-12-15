#include "../includes/generalCS.h"

t_cs				*halt(t_cs *t)
{
	static t_cs		*tmp;
	
	if (t == NULL)
		return (tmp);
	tmp = t;
	return (t);
}

static void			distributor_signals(int code)
{
	t_cs			*cs;
	
	cs = halt(NULL);
	close(cs->sockfd);
	exit(code);
}

void				get_signal(void)
{
	signal(SIGINT,  distributor_signals);
	signal(SIGSTOP, distributor_signals);
	signal(SIGABRT, distributor_signals);
	signal(SIGQUIT, distributor_signals);
	signal(SIGKILL, distributor_signals);
	signal(SIGTERM, distributor_signals);
}
