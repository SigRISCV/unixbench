#ifndef __RAWCODE_H__
#define __RAWCODE_H__

extern __raw volatile unsigned long iter;

__raw void second_report();
__raw void minute_report();

struct ChildInfo {
	int	xmit;	/* # characters sent */
	char	*bp;	/* std input buffer pointer */
	int	blen;	/* std input buffer length */
	int	fd;	/* stdin to command */
	int	pid;	/* child PID */
	char	*line;	/* start of input line */
	int	firstjob;	/* inital piece of work */
	int	thisjob;	/* current piece of work */
};

#define GRANULE		5
#define DEF_RATE	5.0
#define DEF_RATE	5.0
#define GRANULE		5
#define CHUNK		60
#define MAXCHILD	12
#define MAXWORK		10
extern volatile float	thres;
extern volatile float	est_rate;
extern int	firstuser;
extern int	exit_status;
extern int	sigpipe;
extern int	nusers;
extern struct ChildInfo child[MAXCHILD];

__raw void onalarm(int foo);
__raw void grunt();
__raw void pipeerr();
__raw void wrapup(const char *reason);

extern int sigalarm;
extern char FNAME0[18];
extern char FNAME1[18];

__raw void stop_count();
__raw void clean_up();

#endif /* __RAWCODE_H__ */