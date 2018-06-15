
#include "timer.h"

struct timespec		*init_clock(int set_time)
{
  struct timespec	*clock;

  if (!(clock = malloc(sizeof(*clock))))
    return (NULL);
  if (set_time)
    clock_gettime(CLOCK_REALTIME, clock);
  return (clock);
}

double			calc_clock_elapsed(struct timespec *timer)
{
  struct timespec	now;
  double		time_elapsed;

  clock_gettime(CLOCK_REALTIME, &now);
  time_elapsed = (now.tv_sec - timer->tv_sec);
  time_elapsed += ((now.tv_nsec - timer->tv_nsec) / CLOCK_PRECISION);
  return (time_elapsed);
}

struct timeval		*init_timer(int reset)
{
  struct timeval	*timer;

  if (!(timer = malloc(sizeof(*timer))))
    return (NULL);
  if (reset)
    gettimeofday(timer, NULL);
  return (timer);
}

long			calc_timer_elapsed(struct timeval *timer)
{
  struct timeval	zero;
  long			time;

  if (!timer)
    return (-1);
  gettimeofday(&zero, NULL);
  time = (zero.tv_sec - timer->tv_sec) * 1000.0;
  time += (zero.tv_usec - timer->tv_usec) / 1000.0;
  return (time);
}
