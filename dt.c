#include <stdio.h>
#include <time.h>
int main() {
    struct tm *tm;
    time_t now;
    time(&now);
    tm = localtime(&now);
    tm->tm_year += 1900;
    tm->tm_mon += 1;
    tm->tm_mday += 1;
    tm->tm_hour += 1;
    tm->tm_min += 1;
    tm->tm_sec += 1;
    printf("%04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    return 0;
}