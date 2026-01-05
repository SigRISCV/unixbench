#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "rawcode.h"

volatile unsigned long iter;

void second_report()
{
	fprintf(stderr,"COUNT|%ld|1|lps\n", iter);
	exit(0);
}

void minute_report()
{
    fprintf(stderr,"COUNT|%lu|60|lpm\n", iter);
	exit(0);
}

volatile float	thres;
volatile float	est_rate = DEF_RATE;
void onalarm(int foo)
{
    thres += est_rate;
    signal(SIGALRM, onalarm);
    alarm(GRANULE);
}

int	firstuser;	/* ordinal identification of first user for this
			 * process */
int	exit_status = 0;	/* returned to parent */
int	sigpipe;	/* pipe write error flag */
int	nusers;		/* number of concurrent users to be simulated by
			 * this process */
struct ChildInfo child[MAXCHILD];

void grunt()
{
    /* timeout after label "bepatient" in main */
    exit_status = 4;
    wrapup("Timed out waiting for jobs to finish ...");
}

void pipeerr()
{
	sigpipe++;
}

void wrapup(const char *reason)
{
    int i;
    int killed = 0;
    fflush(stderr);
    for (i = 0; i < nusers; i++) {
	if (child[i].pid > 0 && kill(child[i].pid, SIGKILL) != -1) {
	    if (!killed) {
		killed++;
		fprintf(stderr, "%s\n", reason);
		fflush(stderr);
	    }
	    fprintf(stderr, "user %d job %d pid %d killed off\n", firstuser+i, child[i].thisjob, child[i].pid);
	fflush(stderr);
	}
    }
    exit(exit_status);
}

int sigalarm = 0;

void stop_count()
{
        sigalarm = 1;
}

char FNAME0[18] = "dummy0-XXXXXXXXXX";
char FNAME1[18] = "dummy1-XXXXXXXXXX";

void clean_up()
{
        unlink(FNAME0);
        unlink(FNAME1);
}