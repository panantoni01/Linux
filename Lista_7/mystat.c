#include<stdlib.h>
#include<stdio.h>
#include<getopt.h>
#include<fcntl.h>
#include<errno.h>
#include<signal.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<stdint.h>
#include<unistd.h>

FILE* ofile; /* /var/log/mystat.log or user-defined file */ 
FILE* ifile; /* /proc/stat file */
char* logfile = "/var/log/mystat.log";

static _Noreturn void arg_missing_error(char *opt) {
    fprintf(stderr, "Argument missing for %s option!\n", opt);
    exit(EXIT_FAILURE);
}
static _Noreturn void invalid_arg_error(char *opt) {
    fprintf(stderr, "Invalid argument for %s option!\n", opt);
    exit(EXIT_FAILURE);
}

static void sighup_handler(int signo) {
    if (fclose(ofile)) {
        fprintf(stderr, "fclose error %s\n", strerror(errno));
        exit(1);
    }
    if ((ofile = fopen(logfile, "a")) == NULL) {
        fprintf(stderr, "fopen error: %s\n", strerror(errno));
        exit(1);
    }
}


int main(int argc, char* argv[]) {
    int period = 1;
    int interval = 60;

    static struct option long_options[] = {
        {"interval", required_argument, NULL, 'i'},
        {"logfile", required_argument, NULL, 'f'},
        {"period", required_argument, NULL, 'p'},
        {NULL, 0, NULL, 0}
    };

    int choice = 0;
    while ((choice = getopt_long(argc, argv, "i:f:p:", long_options, NULL)) != -1) {
        switch (choice) {
            case 'i':
                if (!optarg)
                    arg_missing_error("--interval");
                interval = atoi(optarg);
                if (interval <= 0)
                    invalid_arg_error("--interval");
                break;
            
            case 'f':
                if (!optarg)
                    arg_missing_error("--logfile");
                logfile = optarg;
                break;
            
            case 'p':
                if (!optarg)
                    arg_missing_error("--period");
                period = atoi(optarg);
                if (period <= 0)
                    invalid_arg_error("--period");
                break;
            
            default:
                exit(1);
        }
    }

    signal(SIGHUP, sighup_handler);
    
    if ((ofile = fopen(logfile, "a")) == NULL) {
        fprintf(stderr, "fopen error: %s\n", strerror(errno));
        exit(1);
    }

    uint64_t time_elapsed = 0;
    uint64_t time_total_sum = 0, time_idle_sum = 0;
    uint64_t time_total_start, time_idle_start;
    while(1) {
        if (time_total_sum == 0) {
            time_total_start = 0;
            time_idle_start = 0;
            
            if ((ifile = fopen("/proc/stat", "r")) == NULL) {
                fprintf(stderr, "fopen error: %s\n", strerror(errno));
                exit(1);
            }
            
            char cpu_name[256];
            fscanf(ifile, "%s", cpu_name);
            for (int i = 1; i <= 10; i++) {
                uint64_t timeval = 0;
                fscanf(ifile, "%ld", &timeval);
                time_total_start += timeval;
                if (i == 4)
                    time_idle_start += timeval;
            }
            
            if (fclose(ifile)) {
                fprintf(stderr, "fclose error %s\n", strerror(errno));
                exit(1);
            }
        }
        
        sleep(1);
        time_elapsed++;
        
        if (time_elapsed % (uint64_t)period == 0) {
            if ((ifile = fopen("/proc/stat", "r")) == NULL) {
                fprintf(stderr, "fopen error: %s\n", strerror(errno));
                exit(1);
            }
            
            char cpu_name[256];
            fscanf(ifile, "%s", cpu_name);
            for (int i = 1; i <= 10; i++) {
                uint64_t timeval = 0;
                fscanf(ifile, "%ld", &timeval);
                time_total_sum += timeval;
                if (i == 4)
                    time_idle_sum += timeval;
            }
            time_total_sum -= time_total_start;
            time_idle_sum -= time_idle_start;
            
            if (fclose(ifile)) {
                fprintf(stderr, "fclose error %s\n", strerror(errno));
                exit(1);
            }
        } 
        if (time_elapsed % (uint64_t)interval == 0) {
            time_t now;
            time(&now);
            struct tm *local = localtime(&now);
            fprintf(ofile,"%d-%02d-%02d %02d:%02d:%02d CPU usage %.2f %%\n", 
                local->tm_year+1900, local->tm_mon, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec, 
                (100.0 - ((double)time_idle_sum/(double)time_total_sum)*100.0));
            fflush(ofile);
            time_total_sum = 0;
            time_idle_sum = 0;
        }
    }

    if (fclose(ofile)) {
        fprintf(stderr, "fclose error %s\n", strerror(errno));
        exit(1);
    }
    return 0;
}