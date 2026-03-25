#include <stdio.h>
#include <time.h>
#include <string.h>

int main(int argc, char** argv)
{
	if (argc > 2) {
		fprintf(stderr, "Usage: dt [--iso-time | --us-time] [-ds=<char>] [-ts=<char>]\n");
		return 1;
	}

	char date_separator = '/';
	int iso_time = 0, us_time = 0;
	char time_separator = ':';

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--iso-time") == 0 || strcmp(argv[i], "-iso") == 0) {
			iso_time = 1;
		}
		else if (strcmp(argv[i], "--us-time") == 0 || strcmp(argv[i], "-us") == 0) {
			us_time = 1;
		}
		else if (strncmp(argv[i], "--date-separator=", 17) == 0) {
			date_separator = argv[i][17];
		}
		else if (strncmp(argv[i], "-ds=", 4) == 0) {
			date_separator = argv[i][4];
		}
		else if (strcmp(argv[i], "--help") == 0) {
			printf("Usage: dt [--iso-time | --us-time] [-ds=<char>] [-ts=<char>]\n");
			return 0;
		}
		else if (strcmp(argv[i], "--time-separator=") == 0) {
			time_separator = argv[i][17];
		}
		else if (strcmp(argv[i], "-ts=") == 0) {
			time_separator = argv[i][4];
		}
		else {
			fprintf(stderr, "Unknown option: %s\n", argv[i]);
			return 1;
		}
	}
   time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    /* tm_year is years since i900; tm_mon is 0-based; rest are already correct */
    if (iso_time) {
		printf("%04d%c%02d%c%02d\n", tm->tm_year + 1900, date_separator, tm->tm_mon + 1, date_separator, tm->tm_mday);
    }
    else if (us_time) {
        printf("%02d%c%02d%c%04d\n", tm->tm_mon + 1, date_separator, tm->tm_mday, date_separator, tm->tm_year + 1900);
    }
	else{
	    printf("%02d%c%02d%c%04d\n", tm->tm_mday, date_separator, tm->tm_mon + 1, date_separator, tm->tm_year + 1900);
    }
	printf("%02d%c%02d%c%02d\n", tm->tm_hour, time_separator, tm->tm_min, time_separator, tm->tm_sec);

    return 0;
}
