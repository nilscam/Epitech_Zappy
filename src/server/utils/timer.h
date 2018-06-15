
#ifndef TIMER_H_
# define TIMER_H_

# include <unistd.h>
# include <time.h>
# include <stdlib.h>
# include <sys/time.h>

# define CLOCK_PRECISION	1E9

/*		timer.c				*/
struct timespec		*init_clock(int);
double			calc_clock_elapsed(struct timespec *);
struct timeval		*init_timer(int reset);
long			calc_timer_elapsed(struct timeval *);

#endif /* !TIMER_H_ */
