#include <stdio.h>
#include <time.h>

int main(void)
{
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    /* tm_year is years since 1900; tm_mon is 0-based; rest are already correct */
    printf("%04d-%02d-%02d %02d:%02d:%02d\n",
        tm->tm_year + 1900,
        tm->tm_mon + 1,
        tm->tm_mday,
        tm->tm_hour,
        tm->tm_min,
        tm->tm_sec);
    return 0;
}