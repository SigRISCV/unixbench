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