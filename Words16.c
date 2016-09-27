/****************************************************************
Name: Austin Lachance
Email: austin.lachance@yale.edu

CPSC223
This program sorts a matrix of chars from an INITIAL config
to a GOAL config using the fewest number of pancake flips
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "tree.h"

// Print message to stderr and exit.
#define DIE(msg)	exit (fprintf (stderr, "%s\n", msg))

//Parses a file (fp) word by word
char *getWord(FILE *fp);


int main(int argc, char *argv[]) {
	int index = 1;
	int IF = 0;
	char* helper;
	char* line;
	FILE *fp;
	Tree t;
	create(&t);

	while(index < argc) {

		if(strcmp(argv[index], "-d") == 0) {
			index++;

			fp = fopen(argv[index], "r");
			if(fp == NULL) {
				DIE("File does not exist");
			}
			while((line = getWord(fp)) != NULL) {

				if(*line != '@') {
					delete(&t, line);
				}
				free(line);
			}
			fclose(fp);
		}
		else if(strcmp(argv[index], "-print") == 0) {
			inorder(t);
		}
		else if(strcmp(argv[index], "-dump") == 0) {
			preorder(t);
		}
		else if(strcmp(argv[index], "-epl") == 0) {
			epl(t);
		} 
		else if(strcmp(argv[index], "-set") == 0) {
			index++;
			IF = strtol(argv[index], &helper, 10);
			change_IF(IF);
		}
		else {

			fp = fopen(argv[index], "r");
			if(fp == NULL) {
				DIE("File does not exist");
			}
			while((line = getWord(fp)) != NULL) {
				if(*line != '@') {
					searchInsert(&t, line);
				}
				free(line);
			}
			fclose(fp);
		}
		index++;
	}

	exit(0);
	return 0;
}

//Slightly altered version of getLine written by Professor Stan Eisenstat
char *getWord(FILE *fp)
{

    char *line;
    int size;
    int c, i;

    size = sizeof(double);
    line = malloc (size);

    for (i = 0;  (c = getc(fp)) != EOF; )  {
		if (i == size-1) {
		    size *= 2;
		    line = realloc (line, size);
		}
		if (!isalnum(c)) {
		    break;	
		}
		line[i++] = tolower(c);
    }
    if (c == EOF && i == 0)  {
	free (line);
	return NULL;
    }

    if(i == 0) {
     	line[i] = '@';
    	i=2;
    }
    line[i++] = '\0';
    line = realloc (line, i);
    return (line);
}
