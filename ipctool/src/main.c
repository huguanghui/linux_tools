#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "backup.h"

void Help()
{
    printf("\nipctool is to support development cost and lang-term maintenance of what we"
           "believe will serve a fundamental role in the advancement of a stable"
           "available options:\n"
           "\t--chip_id\n"
           "\t--sensor_id\n"
           "\t--temp\n"
           "\n"
           "\t--demsg\n");
    return;
}

int main(int argc, char** argv)
{
    const char* short_options = "";
    const struct option long_options[] = {
        { "help", no_argument, NULL, 'h' },
        { "upgrade", optional_argument, NULL, 'u' },
        { NULL, 0, NULL, 0 },
    };

    int rez;
    int option_index;
    bool skip_env = false;
    bool force = false;

    while ((rez = getopt_long_only(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (rez) {
        case 'h':
            Help();
            return 0;
        case 'u':
            return do_upgrade(optarg, force);
        default:
            printf("found unknown option\n");
        case '?':
            Help();
            return EXIT_FAILURE;
        }
    }
    return 0;
}
