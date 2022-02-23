/* 
* Author : Amanda Kwong
* Description: HW4
*	
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 200

char ** fgetLines(FILE* f, int *nl)
{
    char** lines;
    int i = 0;
    char   *line = calloc(1000,sizeof(char));
    int    line_count;
    int    line_length;
    *nl = 0;
    line_count = 0;
    while (fgets(line, 1000, f) != NULL) {
      line_count++;
    }
    rewind(f);
    lines = calloc(line_count,sizeof(char*));
    for (i = 0; i < line_count; i++) {
        fgets(line, 1000, f);
        line_length = strlen(line);
        line[line_length] = '\0';
        lines[i] = calloc((line_length+1),sizeof(char));
        memcpy(lines[i],line,strlen(line));
    }
    *nl = line_count;
    return lines;
}


char ** sgetWords(char *line, int *nw)
{
  char** words;
  char buffer[1000];
  char buffer2[1000];
  char *token;
  int count = 0;
  for (int i = 0; i < strlen(line); i++)
    if (line[i] != ' ')
      buffer[count++] = line[i];
  buffer[count] = '\n';
  buffer[count++] = '\0';
  int state = 0;
  for (int j = 0, k = 0; j < strlen(buffer); j++) {
    if (isalnum(buffer[j]) || buffer[j] == ',')
      buffer2[k++] =  buffer[j];
  }
  *nw = 0;
  for (int i = 0; buffer2[i]; i++) {
    if (buffer2[i] == ' ' || buffer2[i] == '\n' || buffer2[i] == '\t' || buffer2[i] == ',')
      state = 0;
    else if (state == 0) {
      state = 1;
      ++(*nw);
    }
  }
  printf("%d\n", *nw);
  printf("%s\n", buffer2);
//  array2 = (char **)malloc((*nw)*sizeof(char *));
  token = strtok(buffer2,',');
  for (int i = 0; token != NULL; i++ ) {
    printf("%s\n", token );
    words[i] = (char *)calloc(strlen(token),sizeof(char *));
    token = strtok(NULL,',');
    memcpy(words[i],token,strlen(token));
    printf("%s %s\n", wordsarray2[i], token);
  }
  return words;
}


char* cPrefix(char **words, int nw)
{

	char *str = malloc(MAX);
	char end = 0;
	int k = 0;
	for (int i = 0; words[0][i] != 0; i++){
		for (int j = 1; j < nw; j++) {
			if (words[j][i] != words[0][i]){ 
				end = 1;
				break;
			}
		}
		if (end) {
			break;
		}
		else {
			str[k++] = words[0][i];
		}
	}
	str[k] = 0;
	return str;

}


/*
	Do not modify the main function when submit.
	You can modify it when doing your homework.
*/

int main(int argc, char *argv[])
{

	// Get test file name from commandline or default to test.txt
	char *fs = argc>2 ? argv[1] : "test.txt";
	FILE *f = fopen(fs,"r");	
	
	// Read each line into lines, nl is the number of lines
	
	int nl=0, nw=0;
	char **lines = fgetLines(f, &nl);

	for (int i = 0; i < nl; ++i)
	{	
		
			/* Read each word into words, nw is the number of words for each line
			words should have separate memory than lines[i] */
				
		nw=0;
		char **words= sgetWords(lines[i], &nw);
		if (nw==0) continue;
		
		printf("\nTotal: %d\n", nw);
		for (int i = 0; i < nw; ++i) printf("%s, ", words[i]);
		printf("\nThe common prefix is: %s\n", cPrefix(words,nw));
		
		for (int i = 0; i < nw; ++i) free(words[i]);		
		free(words);

	}

	for (int i = 0; i < nl; ++i) free(lines[i]);		
	free(lines);
	fclose(f);



	return 0;
}
