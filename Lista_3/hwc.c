#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

static _Noreturn void arg_missing_error(char *opt)
{
    fprintf(stderr, "Argument missing for %s option!\n", opt);
    exit(EXIT_FAILURE);
}

static _Noreturn void invalid_argument_error(char *opt)
{
    fprintf(stderr, "Invalid argument for %s option\n", opt);
    exit(EXIT_FAILURE);
}

static void help()
{
    puts("SYNOPSIS\n\tusage: ./hwc [-cwhv] [-g text] [--color=WHEN] ARGS...\n");
    puts("OPTIONS");
    puts("\t-c, --capitalize\n\
              when written to the output, all arguments from ARGS and optional\n\
              'world' (see -w option) will begin with a capital letter\n");
    puts("\t--color=WHEN\n\
              colorize  the  output;  WHEN can be 'always', 'auto' (default if\n\
              omitted) , or 'never'; more info below\n");
    puts("\t-g, --greeting=text\n\
              print text instead of standard \"Hello\" greeting\n");
    puts("\t-h, --help\n\
              display this help and exit\n");
    puts("\t-v, --version\n\
              display version and copyright information and exit\n");
    puts("\t-w, --world\n\
              append the output with traditional \"Hello, world!\" greeting\n");
}

static void version()
{
    printf("APokusinski 15.03.2021\nAll rights reserved\n");
}

int main(int argc, char *argv[])
{
    int cap = 0;
    int world = 0;
    char *greet = "Hello";
    char *color = "auto";
    static int col = 0;

    static struct option long_options[] = {
        {"capitalize", no_argument, NULL, 'c'},
        {"greeting", required_argument, NULL, 'g'},
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {"world", no_argument, NULL, 'w'},
        {"color", required_argument, &col, 1},
        {NULL, 0, NULL, 0}};

    int choice = 0;

    while ((choice = getopt_long(argc, argv, "cg:hvw", long_options, NULL)) != -1)
    {
        switch (choice)
        {
        /* For a long option,
            they return val if flag is NULL, and 0 otherwise. */
        case 0: 
            if (!optarg)
                arg_missing_error("--color");
            color = optarg;
            // printf("col variable is: %d\n", col);
            // printf("color : %s\n", color);
            break;
        case 'c':
            cap = 1;
            break;
        case 'g':
            if (!optarg)
                arg_missing_error("--greeting");
            greet = optarg;
            // printf("greeting : %s\n",greet);
            break;
        case 'h':
            help();
            exit(EXIT_SUCCESS);
            break;
        case 'v':
            version();
            exit(EXIT_SUCCESS);
            break;
        case 'w':
            world = 1;
            break;
        default:
            help();
            exit(EXIT_FAILURE);
        }
    }
    
    argc -= optind;
    argv += optind;

    for (int i = 0; i < argc; i++)
    {
        if (cap)
            argv[i][0] = toupper(argv[i][0]);

        if (!strcmp(color, "auto"))
        {
            if (isatty(1))
                printf("%s, \033[1;32m%s\033[0m!\n", greet, argv[i]);
            else
                printf("%s, %s!\n", greet, argv[i]);
        }
        else if (!strcmp(color, "never"))
            printf("%s, %s!\n", greet, argv[i]);
        else if (!strcmp(color, "always"))
            printf("%s, \033[1;32m%s\033[0m!\n", greet, argv[i]);
        else
            invalid_argument_error("--color");
    }

    /* Append the output with 'world' greeting if required */
    if (world)
    {
        char *arg;
        if (cap)
            arg = "World";
        else
            arg = "world";

        if (!strcmp(color, "auto"))
        {
            if (isatty(1))
                printf("%s, \033[1;32m%s\033[0m!\n", greet, arg);
            else
                printf("%s, %s!\n", greet, arg);
        }
        else if (!strcmp(color, "never"))
            printf("%s, %s!\n", greet, arg);
        else if (!strcmp(color, "always"))
            printf("%s, \033[1;32m%s\033[0m!\n", greet, arg);
        else
            invalid_argument_error("--color");
    }

    return 0;
}