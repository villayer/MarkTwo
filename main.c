/***************************************************** 
 * MarkTwo: a tool for converting markdown into Html
 * Author: Villayer 
 * Usage:
 *
*****************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_file(char *);
void display_help(void);

int main(int argc, char **argv) {
    
    // argv[i]
    // 0 - path
    // 1 - flag
    // 2 - file

    // check for the '-' flag and determine the flag used
    if(argv[1] != 0 && '-' == argv[1][0]) {
        
        switch(argv[1][1]) {
            case 'f': parse_file(argv[2]);
                      break;

            case 'h': display_help(); 
                      break;

            default: puts("please provide a valid option");
                     puts("for help run use -h");
        }
    }
    
    else {
        fprintf(stderr, "Error: no option was specified!\n");
        printf("Hint: use -h for help\n");
    }

    
    

    return 0;
}

void display_help(void) {

    puts("Help: usage guide");
    puts("Options");
    puts(" -f   file option, used to specify a file to convert");
    puts(" -h   help option, used to display this help menu");

}


int parse_file(char *file_name) {

    FILE *f = fopen(file_name, "r");
    FILE *fout = fopen("out.html", "w");

    if(!f) {
        fprintf(stderr, "Could not open %s: ", file_name);
        perror("");
        return -1;
    }
    
    char buff[30];
    char bigbuff[1024];

    int inside_header = 0;
    int hlen;

    // read a line to bigbuff
    while(fgets(bigbuff, sizeof(bigbuff), f) != NULL) {
        
        // scan individual line
        while(sscanf(bigbuff, "%s", buff) > 0) {
            
            // scan for a header
            if (strncmp("#", buff, 1) == 0) {
                hlen = strlen(buff);
                
                if (hlen > 6) {
                    fprintf(stderr, "Header Length incompatible\n");
                    break;
                }

                fprintf(fout, "<h%d>\n", hlen);
                inside_header = 1; 
            }

            if (inside_header = 0)
                fprintf(fout, "%s ", buff);

            else {
                fprintf(fout, "%s\n", bigbuff);
                fprintf(fout, "<h%d/>\n", hlen);
            }
        }

    }

    fclose(fout); 
    fclose(f);
    return 0;
}
