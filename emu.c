#include <stdio.h>
#include <stdlib.h>

void usage (char *prog);

int main (int argc, char *argv[]) {
    if (argc != 2) {
        usage(argv[0]);
        exit(1);
    }
    
    FILE *fp = fopen(argv[1], "rb");
    
    if (fp == NULL) {
        fprintf(stderr, "ERROR: file '%s' not found!\n", argv[1]);
        exit(1);
    }
    
    char bytes[4] = {0};
    int ch = '0';
    int i = 0;
    
    while ( ch != EOF ) {
        if (i == 4) {
            fprintf(stdout, "OPC: %2u | OP1: %2u | OP2: %2u | OP3: %2u\n", 
                                        ( (bytes[1] << 4) ^ (bytes[2] >> 4) ) & 0x3f, 
                                        bytes[2] & 0xf, 
                                        (bytes[3] & 0xf0) >> 4, 
                                        bytes[3] & 0xf);
            i = 0;
        } else {
            bytes[i] = ch = fgetc(fp);
            i++;
        }
    }                        
        
    fclose(fp); 
    return 0;
}


void usage (char *prog) {
    fprintf(stdout, "Usage: %s <filename>\n", prog);
}
