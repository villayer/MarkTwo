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
int copy_upper(FILE *);
int copy_lower(FILE *);

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
    
    char *output_name = "out.html";

    FILE *f = fopen(file_name, "r");
    FILE *out = fopen(output_name, "w");

    if(!f) {
        fprintf(stderr, "Could not open %s: ", file_name);
        perror("");
        return -1;
    }
    
    if(!out) {
        fprintf(stderr, "Could not open %s: ", output_name);
        perror("");
        return -1;
    }
    
    copy_upper(out);


    int hlen = 0; // header length
    int len = 0;  // real buffer length
    char buff[500]; // buffer [MAX_LENGTH]

    // read a line to big
    while(fgets(buff, sizeof(buff), f) != NULL) {

        len = strlen(buff);
        
        for(int i = 0; i <len - 1; i++) {
            if(buff[i] == '#') {
                hlen++;
            }
        }

        if (hlen != 0) {
            if (hlen < 1 || hlen > 6) {
                fprintf(stderr, "Error: header length error\n");
                break;
            }

            fprintf(out, "<h%d>\n", hlen);
            
            for(int i = hlen; i < len - 1; i++)
                fputc(buff[i], out);
            fprintf(out, "\n<h%d/>\n", hlen);

            hlen = 0;
        }

        else {
            // for(int i = 0; i < len - 1; i++)
            fputs(buff, out);
        }
    }

    fputc('\n', out);
    copy_lower(out);
    

    fclose(out); 
    fclose(f);
    return 0;
}


int copy_upper(FILE *f) {
    FILE *upper = fopen("__upper.html", "r");
    
    if (!upper)
    {
        perror("copy_upper:");
        return -1;
    }

    char buff[512];
    while( fgets(buff, sizeof(buff), upper) != NULL )
        fputs(buff, f);

    fclose(upper);
    return 0;
}

int copy_lower(FILE *f) {
    FILE *lower = fopen("__lower.html", "r");
    
    if (!lower)
    {
        perror("copy_lower:");
        return -1;
    }

    char buff[512];
    while( fgets(buff, sizeof(buff), lower) != NULL )
        fputs(buff, f);

    fclose(lower);
    return 0;
}
