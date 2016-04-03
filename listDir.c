/*
 * List file and count file in directory pass by argument.
 *
 * ***** USAGE***** 
 *
 * command [directory path]
 *
 * */


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>

#define BOLD "\033[1m"
#define WHITE "\033[0m"
#define RED  "\033[22;31m"
#define GREEN  "\033[22;32m"
#define YELLOW  "\033[22;33m"
#define BLUE  "\033[22;34m"
#define LBLUE  "\033[22;36m"
#define PURPLE  "\033[22;35m"
#define BLACK  "\033[22;30;47m"
#define INVLBLUE  "\033[22;30;46m"
#define INVRED  "\033[22;30;41m"
#define INVYEL  "\033[22;30;43m"

int listRec(char *dir_name, int *dr, int *rg, int *sym, int *chr, int *sock, int *blk, int *unkn);


int listRec(char *dir_name, int *dr, int *rg, int *sym, int *cr, int *sck, int *bl, int *unk){
    DIR *dir_stream;
    struct dirent *entry;
    const char *d_name;

    /* Open the directory */
    dir_stream = opendir(dir_name);

    /* Check it was opened. */
    if(!dir_stream){
        fprintf(stderr, "Problem opening directory '%s': %s\n",
                 dir_name, strerror (errno));
        //exit (EXIT_FAILURE);
        return 1;
    }
    /* Check all the entries of the directory "d". Do it in a "while" for check
     * every NEXT directory entry in the directory stream. */
    
    while((entry = readdir(dir_stream)) != NULL){
        
        d_name = entry->d_name;
        if((strcmp(d_name, "..") != 0 &&
                strcmp(d_name, ".") != 0)){
            /* Print the name of the directory entry */
            if(entry->d_type == DT_REG){
                (*rg)++;
                printf(" |__%sRegular file%s %s/%s%s%s\n", BOLD, BLUE, dir_name, GREEN, d_name, WHITE);
            }
            if(entry->d_type == DT_LNK){
                (*sym)++;
                char buf[100];
                readlink(entry->d_name, buf, 100);
                printf(" |__%sLink file: %s@%s%s -> %s%s%s\n", BOLD, YELLOW, entry->d_name, WHITE, GREEN, buf, WHITE);
            }
            if(entry->d_type == DT_CHR){
                (*cr)++;
                printf(" |__%sChar device %s%s/%s%s\n", BOLD, INVYEL, dir_name, WHITE, d_name);
            }
            if(entry->d_type == DT_SOCK){
                (*sck)++;
                printf(" |__%sSocket %s%s/%s%s\n", BOLD, INVLBLUE, dir_name, WHITE, d_name);
            }
            if(entry->d_type == DT_BLK){
                (*bl)++;
                printf(" |__%sBlock device %s%s/%s%s\n", BOLD, BLACK, dir_name, WHITE, d_name);
            }
            if(entry->d_type & DT_UNKNOWN){
                (*unk)++;
                printf(" |__%sUnknown file %s%s/%s%s\n", BOLD, INVRED, dir_name, WHITE, d_name);
            }
        }
        
        if(entry->d_type == DT_DIR){
            /* Do not look for current and partent directories */
            if(strcmp(d_name, "..") != 0 &&  strcmp(d_name, ".") != 0){
                int path_length;
                char path[PATH_MAX];
                (*dr)++;
 
                path_length = snprintf(path, PATH_MAX,
                                        "%s/%s", dir_name, d_name);
                printf("|_%sFOLDER %s%s/%s%s\n", BOLD, BLUE, dir_name, d_name, WHITE);
                
                if(path_length >= PATH_MAX){
                    fprintf(stderr, "Path too long.\n");
                    exit(EXIT_FAILURE);
                }
                /* Recursively call "listRec" in the found directory */
                listRec(path,dr,rg,sym,cr,sck,bl,unk);
            }
	    }

        


    }//close while()

    /* Close the directory stream */
    if(closedir(dir_stream)){
        fprintf(stderr, "Problem with '%s': %s\n", dir_name, strerror (errno));
        exit(EXIT_FAILURE);
    }
    return 0;
}

int main(int argc, char *argv[]){
    int reg = 0;
    int dir = 0;
    int symb = 0;
    int chr = 0;
    int sock = 0;
    int blk = 0;
    int unkn = 0;
    int *dirp = &dir;
    int *regp = &reg;
    int *symbp = &symb;
    int *chrp = &chr;
    int *sockp = &sock;
    int *blkp = &blk;
    int *unknp = &unkn;
    char *c = argv[1];

    /* clean the passed argument */
    if(( (c[strlen(c)-1]) == '.') && ((c[strlen(c)-2]) == '/')){
        c[strlen(c)-1] = 0;
        c[strlen(c)-1] = 0;
    }

    int ris = listRec(argv[1],dirp,regp,symbp,chrp,sockp,blkp,unknp);
    if (ris == 0){
        printf("\n%sIn this directory %s\n", BOLD, WHITE);
        printf(" %sdirectories%s:  %d\n", BLUE, WHITE, *dirp);
        printf(" %sregular files%s: %d\n", GREEN, WHITE, *regp);
        printf(" %ssymbolic links%s: %d\n", YELLOW, WHITE, *symbp);
        printf(" %schar devices%s: %d\n", INVYEL, WHITE, chr);
        printf(" %sblock devices%s: %d\n", BLACK, WHITE, blk);
        printf(" %sunix sockets%s: %d\n", INVLBLUE, WHITE, sock);
        printf(" %sunknown files%s: %d\n", RED, WHITE, unkn);
    }else{
        printf("\nSYNOPSIS:\n\n\tcommand [directory path]\n\n");
    }
    return 0;
}
