/* A simple fastfetch like program in C no configs no bloat just a simple fetch program that prints the system information (and ascii art) in a nice format. */
/* ascii art is on the left and the system information is on the right. */
/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <pwd.h>
#include <time.h>
#include <sys/statvfs.h>
#include <string.h>

/* color codes */
#define YEL "\033[33m"
#define WHT "\033[97m"
#define RST "\033[0m"

int main(void){
    struct utsname uinfo;
    uname(&uinfo);
    long long totalram = (long long) sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE);
    long long usedram = (long long) sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGESIZE);
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    long uptime = ts.tv_sec;
    long days = uptime / 86400;
    long hours = (uptime % 86400) / 3600;
    long minutes = (uptime % 3600) / 60;
    struct statvfs diskinfo;
    statvfs("/", &diskinfo);
    struct passwd *pw = getpwuid(getuid());
    char *username = pw->pw_name;
    char *hostname = uinfo.nodename;
    char *os = uinfo.sysname;
    char *kernel = uinfo.release;
    const char *ram_unit = "B";
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

    if (totalram >= 1099511627776) {
        totalram = totalram / 1099511627776;
        usedram = usedram / 1099511627776;
        ram_unit = "TiB";
    } else if (totalram >= 1073741824) {
        totalram = totalram / 1073741824;
        usedram = usedram / 1073741824;
        ram_unit = "GiB";
    } else if (totalram >= 1048576) {
        totalram = totalram / 1048576;
        usedram = usedram / 10498576;
        ram_unit = "MiB";
    } else if (totalram >= 1024) {
        totalram = totalram / 1024;
        usedram = usedram /1024;
        ram_unit = "KiB";
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
    printf("%s  " YEL "Uptime:" RST " " WHT "%ld days, %ld hours, %ld minutes" RST "\n", art[3], days, hours, minutes);
    printf("%s  " YEL "RAM:" RST " " WHT "%lld / %lld %s" RST "\n", art[4], usedram, totalram, ram_unit);
    printf("%s   " YEL "Disk:" RST " " WHT "%.0f / %.1f GB" RST "\n", art[5], useddisk_gb, totaldisk_gb);
    printf("%s   " YEL "Shell:" RST " " WHT "%s" RST "\n",      art[6], shell);
    printf("%s " YEL "Terminal:" RST " " WHT "%s" RST "\n",   pad, terminal);
    printf("%s " YEL "WM:" RST " " WHT "%s" RST "\n",         pad, wm_name);
    printf("%s " YEL "Arch:" RST " " WHT "%s" RST "\n",       pad, cpu_arch);
        return 0;
}
