#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <db.h>
#include "mcddb.h"


#define BUFSZ 1024


int main(int argc, char **argv)
{
    int ret, op, cnt, i;
    extern char *optarg;
    extern int optind;
    DBT value;
    char **keys, **values;

    if (argc < 2 || argc > 4) {
        //usage();
        puts("BLAH");
    }

    op = getopt(argc, argv, "a:d:f:g:l");

    if (open_db(NULL) == 1) {
        puts("Error opening database");
    }

    switch(op) {
        case 'a':
            if (argc == 4 && (optarg != NULL) &&
                    (strlen(optarg) >= 1) &&
                    (argv[optind] != NULL)) {
                ret = add_rec(optarg, argv[optind]);
                if (ret == 1) {
                    printf("Key '%s' exists\n", optarg);
                    exit(EXIT_FAILURE);
                }
                else if (ret < 0) {
                    perror("mcdcli.c: add_rec");
                    exit(EXIT_FAILURE);
                }
                else if (ret > 0) {
                    printf("%i\n", ret);
                    perror("mcdcli.c: add_rec");
                }
                break;
            }
            else {
                //usage();
                puts("BLAH");
            }
    }
}
