#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define MAX_RESULT_LENGTH           128
#define USEAGE_INFO                 "Useage: strftime [options] unixTime \n" \
                                    "-s     time    Time is second of unix time.\n" \
                                    "-m     time    Time is millisecond of unix time."

#ifndef STRF_DEBUG
#define pri_info(format, args...)   printf(format, ##args)
#else
#define pri_info(format, args...)   printf("[%s:%d] " format, __FILE__, __LINE__, ##args)
#endif

static int64_t get_current_time(void);
static time_t format_raw_time(char * str_time, int64_t * ms);
static void get_format_time(char * buffer, time_t time);

int main(int argc, char * argv[])
{
    int ch = 0;
    int64_t ms = 0;
    int64_t opt_time = 0;
    char buffer[MAX_RESULT_LENGTH];

    opterr = 0;
    while((ch = getopt(argc, argv, "s:m:")) != -1)
    {
        switch(ch)
        {
            case 's':
                opt_time = format_raw_time(optarg, NULL);
                break;
            case 'm':
                opt_time = format_raw_time(optarg, &ms);
                break;
            default:
                pri_info("invalid option: %c\n", optopt);
                pri_info("%s\n", USEAGE_INFO);
                return -1;
        }
    }

    if (argc == 2 && opt_time == 0)
    {
        opt_time = format_raw_time(argv[1], NULL);
    }

    memset(buffer, 0, MAX_RESULT_LENGTH);
    get_format_time(buffer, opt_time);
    if (ms == 0)
    {
        pri_info("%s\n", buffer);
    }
    else
    {
        pri_info("%s.%lld\n", buffer, ms);
    }

    return 0;
}

static int64_t get_current_time(void)
{
   struct timeval tv;
   gettimeofday(&tv,NULL);
   return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

static time_t format_raw_time(char * str_time, int64_t * ms)
{
    time_t time = 0;
    if (str_time == NULL)
    {
        return time;
    }

    char result_time[MAX_RESULT_LENGTH];
    for (int i = 0, j = 0; i < strlen(str_time); i++)
    {
        if (str_time[i] >= '0' && str_time[i] <= '9')
        {
            result_time[j++] = str_time[i];
        }
    }

    time = atol(result_time);
    if (ms == NULL)
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