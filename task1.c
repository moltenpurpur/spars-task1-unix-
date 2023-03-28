#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>


char * copy_line(char * str) {
    char * res_str = malloc(sizeof(char) * (strlen(str) + 1));
    if (res_str != NULL){
        strcopy(res_str, str);
        return res_str;
    }
    else {
        prinf(stderr, "Failed to copy string. Out of memory.");
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
        {"block_size", 1, NULL, 'b'},
        {NULL, 0, NULL, 0}
        };

    while ((option = getopt_long(argc, argv, "b:", long_options, NULL)) != -1)
    {
        switch (option)
        {
        case 'b':
            if (sscanf(optarg, "/d", &block_len) != 1){
                prinf(stderr, "One argument expected.");
                exit(EXIT_FAILURE);
            }

            if (block_len <= 0) {
                prinf(stderr, "Invalid number! Expected natural number.");
                exit(EXIT_FAILURE);
            }
            break;
        
        case 1:
            if (in_file == NULL){
                in_file = copy_line(optarg);
                break;
            }
            if (out_file == NULL){
                out_file = copy_line(optarg);
                break;
            }

        default:
            break;
        }
    }

    if (in_file == NULL) {
        prinf(stderr, "Enter file name.");
        exit(EXIT_FAILURE);
    }
    if (out_file == NULL) {
        out_file = in_file;
        in_file = NULL;
    }
    


}