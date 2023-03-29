#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


char * copy_line(char * str) {
    char * res_str = malloc(sizeof(char) * (strlen(str) + 1));
    if (res_str != NULL){
        strcpy(res_str, str);
        return res_str;
    }
    else {
        fprintf(stderr, "Failed to copy string. Out of memory.\n");
        free(res_str);
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

    while ((option = getopt_long(argc, 
                                 argv, 
                                 "b:", 
                                 long_options, 
                                 NULL)) != -1)
    {
        switch (option)
        {
        case 'b':
            if (sscanf(optarg, "%d", &block_len) != 1){
                fprintf(stderr, "One argument expected.\n");
                exit(EXIT_FAILURE);
            }

            if (block_len <= 0) {
                fprintf(stderr, "Invalid number! Expected natural number.\n");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            break;
        }
    }

    in_file = copy_line(argv[optind]);
    out_file = copy_line(argv[optind+1]);
    int in_file_deskr;
    int out_file_deskr;
    
    if (in_file == NULL) {
        fprintf(stderr, "Enter file name.\n");
        exit(EXIT_FAILURE);
    }

    if (out_file == NULL) {
        out_file = in_file;
        in_file_deskr = 0;
        out_file_deskr = open(out_file, 
                              O_WRONLY | O_CREAT | O_TRUNC, 
                              S_IRUSR | S_IWUSR);
        if (out_file_deskr == -1){
            fprintf(stderr, "Failed to open file.\n");
            exit(EXIT_FAILURE);
        }
    }
    else { 
        in_file_deskr = open(in_file, O_RDONLY);

        if (in_file_deskr == -1){
            fprintf(stderr, "Failed to open file1.\n");
            exit(EXIT_FAILURE);
        }

        out_file_deskr = open(out_file, 
                              O_WRONLY | O_CREAT | O_TRUNC, 
                              S_IRUSR | S_IWUSR);
        
        if (out_file_deskr == -1){
            close(in_file_deskr);
            fprintf(stderr, "Failed to open file2.\n");
            exit(EXIT_FAILURE);
        }
    }

    if (strcmp(in_file, out_file) == 0) {
        fprintf(stderr, "Files must not match.\n");
        exit(EXIT_FAILURE);
    }

    char * buffer = malloc(sizeof(char) * block_len + 1);

    if (buffer == NULL){
        fprintf(stderr, "Failed to create buffer. Out of memory.\n");
        exit(EXIT_FAILURE);
    }

    int flag_zero_block;
    int bytes_read;

    while (1) {
        flag_zero_block = 1;
        bytes_read = read(in_file_deskr, buffer, block_len);

        if (bytes_read == -1){
            fprintf(stderr, "Failed to read file.\n");
            exit(EXIT_FAILURE);
        }
        if (bytes_read == 0){break;}

        for (int i = 0; i < bytes_read; i++){
            if (buffer[i] != 0){
                flag_zero_block = 0;
                break;
            }
        }

        if (flag_zero_block == 1){
            if (lseek(out_file_deskr, bytes_read, SEEK_CUR) == -1){
                fprintf(stderr, "Failed to lseek.\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (write(out_file_deskr, buffer, bytes_read) != bytes_read)
        {
            fprintf(stderr, "Failed to write.\n");
            exit(EXIT_FAILURE);
        }
    }

    if (close(in_file_deskr) == -1 || close(out_file_deskr) == -1){
        fprintf(stderr, "Failed to close file.\n");
        exit(EXIT_FAILURE);
    }

    free(in_file);
    free(out_file);
    free(buffer);
}