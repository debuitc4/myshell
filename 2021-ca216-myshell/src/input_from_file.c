/** input_from_file.c
 * Author: Caoimhe De Buitlear, 19378783
 * I acknowledge the DCU Academic Integrity Policy: https://www.dcu.ie/sites/default/files/policy/1_-_integrity_and_plagiarism_policy_ovpaa-v4.pdf
 * References: https://stackoverflow.com/questions/3736210/how-to-execute-a-shell-script-from-c-in-linux
 * https://stackoverflow.com/questions/7920932/how-to-use-fgets-and-store-every-line-of-a-file-using-an-array-of-char-pointer
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include<sys/wait.h> 

// header files
#include "input_from_file.h"

#define MAX 50

/** Function input_from_file
* @params: char "filename"
** description: This function gets input from a batchfile.
** It reads in the input line by line and executes the commands on each line.
**/

int input_from_file(char *filename){
      //initalising char array using dynamic memory location
      char** array = (char **)malloc(MAX * sizeof(char));
      //checking to see if the memory was alllocated successfully
      if (array == NULL) {
            printf("malloc failed\n");
      return -1;}
      else{
            printf("malloc successful \n");
            printf("\n");
      }
            
      char line[100];
      //opening the batchfile for reading
      FILE *file_ptr = fopen(filename, "r");
      
      int i = 0;
      char *eof;
      //reading in lines of the file and storing them in array
      while( (eof = fgets(line, sizeof(line), file_ptr)) != NULL){
            array[i] = strdup(eof);
            i++;
      }

      //looping through array and executing the commands from the file
      for (int v = 0; v < i; v++){
            //forking the process
            pid_t pid = fork();
            if (pid < 0){
                  printf("error\n");
            }
            else if ( (pid == 0) ){
                  //executing the commands from the file using execlp
                  execlp("/bin/sh", "/bin/sh", "-c", array[v], NULL);
                  printf("execlp failed\n");
                  exit(0);
            }
            else{
                  //parent waiting on child to finish
                  wait(NULL);
            }
      }
      //freeing the memory allocated to the array
      free(array);
      fclose(file_ptr);
}      
