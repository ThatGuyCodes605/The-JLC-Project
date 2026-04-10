/* A simple fastfetch like program in C no configs no bloat just a simple fetch program that prints the system information (and ascii art) in a nice format. */
/* ascii art is on the left and the system information is on the right. */
/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <time.h>
#include <string.h>

/* color codes */
#define YEL "\033[33m"
#define WHT "\033[97m"
#define RST "\033[0m"

int main(void){
    struct utsname uinfo;
    uname(&uinfo);
    struct sysinfo meminfo;
    sysinfo(&meminfo);
    struct statvfs diskinfo;
    statvfs("/", &diskinfo);
    struct passwd *pw = getpwuid(getuid());
    char *username = pw->pw_name;
    char *hostname = uinfo.nodename;
    char *os = uinfo.sysname;
    char *kernel = uinfo.release;
    time_t uptime_seconds = meminfo.uptime;
    int days = uptime_seconds / 86400;
    int hours = (uptime_seconds % 86400) / 3600;
    int minutes = (uptime_seconds % 3600) / 60;
    long totalram = meminfo.totalram;
    long freeram = meminfo.freeram;
    const char *ram_unit = "";
    double totaldisk_d = ((long long)diskinfo.f_blocks * (long long)diskinfo.f_frsize);
    double freedisk_d  = ((long long)diskinfo.f_bavail * (long long)diskinfo.f_frsize);
    double useddisk_gb = (((long long)diskinfo.f_blocks - (long long)diskinfo.f_bfree) * (long long)diskinfo.f_frsize) / 1073741824.0;
    double totaldisk_gb = totaldisk_d / 1073741824.0;
    const char *shell = getenv("SHELL");
    const char *terminal = getenv("TERM");
    char wm_name[64] = "unknown";
    char *cpu_arch = uinfo.machine;
    FILE *fp = popen("pgrep -xl dwm 2>/dev/null | awk '{print $2}'", "r");
    if (fp) {
        fgets(wm_name, sizeof(wm_name), fp);
        pclose(fp);
        wm_name[strcspn(wm_name, "\n")] = 0;
        if (wm_name[0] == '\0') strcpy(wm_name, "unknown");
    }

    if (totalram > 1073741824) {
        totalram = totalram / 1073741824; /* Convert to GB */
        ram_unit = "GB";
    }
    if (freeram > 1073741824) {
        freeram = freeram / 1073741824; /* Convert to GB */
        ram_unit = "GB";
    }
    else {
        totalram = totalram / 1048576; /* Convert to MB */
        freeram = freeram / 1048576; /* Convert to MB */
        ram_unit = "MB";
    }
    if (totaldisk_d > 1099511627776.0) {
        totaldisk_d = totaldisk_d / 1099511627776.0;
        freedisk_d = freedisk_d / 1099511627776.0;
    } else if (totaldisk_d > 1073741824.0) {
        totaldisk_d = totaldisk_d / 1073741824.0;
        freedisk_d = freedisk_d / 1073741824.0;
    } else {
        totaldisk_d = totaldisk_d / 1048576.0;
        freedisk_d = freedisk_d / 1048576.0;
    }
    /* ascii art */
    const char *art[] = {
        "       .--.      ",
        "      |o_o |     ",
        "      |:_/ |     ",
        "     //   \\ \\    ",
        "    (|     | )   ",
        "   /'\\_   _/`\\  ",
        "   \\___)=(___/  "
    };
    /* Print the ascii art and the system information */
        const char *pad = "                  ";

    printf("%s  " YEL "%s" RST "@" YEL "%s" RST "\n",          art[0], username, hostname);
    printf("%s  " YEL "OS:" RST " " WHT "%s" RST "\n",         art[1], os);
    printf("%s  " YEL "Kernel:" RST " " WHT "%s" RST "\n",     art[2], kernel);
    printf("%s  " YEL "Uptime:" RST " " WHT "%d days, %d hours, %d minutes" RST "\n", art[3], days, hours, minutes);
    printf("%s  " YEL "RAM:" RST " " WHT "%ld %s / %ld %s" RST "\n",        art[4], freeram, ram_unit, totalram, ram_unit);
    printf("%s   " YEL "Disk:" RST " " WHT "%.0f GB / %.1f GB" RST "\n", art[5], useddisk_gb, totaldisk_gb);
    printf("%s   " YEL "Shell:" RST " " WHT "%s" RST "\n",      art[6], shell);
    printf("%s " YEL "Terminal:" RST " " WHT "%s" RST "\n",   pad, terminal);
    printf("%s " YEL "WM:" RST " " WHT "%s" RST "\n",         pad, wm_name);
    printf("%s " YEL "Arch:" RST " " WHT "%s" RST "\n",       pad, cpu_arch);
        return 0;
}
