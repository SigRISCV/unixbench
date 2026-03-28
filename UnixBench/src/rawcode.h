#ifndef __RAWCODE_H__
#define __RAWCODE_H__

extern __raw volatile unsigned long iter;

__raw void second_report();
__raw void minute_report();

extern int sigalarm;
extern char FNAME0[18];
extern char FNAME1[18];

__raw void stop_count();
__raw void clean_up();

#endif /* __RAWCODE_H__ */