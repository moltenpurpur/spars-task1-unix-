#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>


char * copy_line(char * str) {
    char * res_str = malloc(sizeof(char) * (strlen(str) + 1));
    if (res_str != NULL){
        strcpy(res_str, str);
        return res_str;
    }
    else {
        fprintf(stderr, "Failed to copy string. Out of memory.");
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char *argv[])
{
    char * in_file = NULL;
    char * out_file = NULL;
    int block_len = 4096;
    int option;

    const struct option long_options[] = {
        {"block_size", required_argument, NULL, 'b'},
        {NULL, no_argument, NULL, 0}
        };

    while ((option = getopt_long(argc, argv, "b:", long_options, NULL)) != -1)
    {
        switch (option)
        {
        case 'b':
            if (sscanf(optarg, "%d", &block_len) != 1){
                fprintf(stderr, "One argument expected.");
                exit(EXIT_FAILURE);
            }

            if (block_len <= 0) {
                fprintf(stderr, "Invalid number! Expected natural number.");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            break;
        }
    }

    in_file = argv[optind];
    out_file = argv[optind+1];
    printf("%s\n", in_file);
    printf("%s\n", out_file);
    printf("%d\n", block_len);
    


    // if (in_file == NULL) {
    //     printf(stderr, "Enter file name.");
    //     exit(EXIT_FAILURE);
    // }
    // if (out_file == NULL) {
    //     out_file = in_file;
    //     in_file = NULL;
    // }
}