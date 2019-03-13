#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define MAX_RESULT_LENGTH 128
#define MS_CUR_COUNT 1000000000000
#define USEAGE_INFO "Useage: strftime time(unix time ms/s)"

static int64_t get_current_time(void);
static time_t format_raw_time(int64_t time, int64_t * ms);
static void get_format_time(char * buffer, time_t time);

int main(int argc, char * argv[])
{
    int64_t opt_time = 0;
    int64_t ms = 0;
    char buffer[MAX_RESULT_LENGTH];

    memset(buffer, 0, MAX_RESULT_LENGTH);
    if (argc == 1)
    {
        opt_time = get_current_time();
    }
    else if (argc == 2)
    {
        opt_time = atol(argv[1]);
    }
    else
    {
        printf("%s\n", USEAGE_INFO);
        return 1;
    }

    opt_time = format_raw_time(opt_time, &ms);
    get_format_time(buffer, opt_time);
    if (ms == 0)
    {
        printf("%s\n", buffer);
    }
    else
    {
        printf("%s:%lld\n", buffer, ms);
    }

    return 0;
}

static int64_t get_current_time(void)
{
   struct timeval tv;
   gettimeofday(&tv,NULL);
   return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

static time_t format_raw_time(int64_t time, int64_t * ms)
{
    if (time < MS_CUR_COUNT)
    {
        return time;
    }
    else
    {
        *ms = time % 1000L;
        return time / 1000L;
    }
}

static void get_format_time(char * buffer, time_t time)
{
    if (buffer == NULL)
    {
        return;
    }

    struct tm * timeinfo = NULL;
    timeinfo = localtime(&time);
    strftime (buffer, MAX_RESULT_LENGTH, "%Y/%m/%d %H:%M:%S", timeinfo);
}