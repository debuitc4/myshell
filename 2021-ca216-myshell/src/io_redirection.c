/** io_redirection.c
 * Author: Caoimhe De Buitlear, 19378783
 * I acknowledge the DCU Academic Integrity Policy: https://www.dcu.ie/sites/default/files/policy/1_-_integrity_and_plagiarism_policy_ovpaa-v4.pdf
 * References: https://www.tutorialspoint.com/c_standard_library/c_function_freopen.htm
 * https://ca216.computing.dcu.ie/labs/lab4e/
 * 
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

// header files
#include "io_redirection.h"

/** Function io_redirection
* @params: char array "arr", integer "size"
** description: This function handles input and output redirection.
**/

int io_redirection(char **arr, int size){
      char *input_f;
      char *output_f;
      char *outf;
      int option = -1;
      int option2 = 0;

      //checking if the symbol is at the first index, error if it is
      if (!(strcmp(arr[0], "<"))){
            printf("No redirection file specified\n");
         }
      else if (!(strcmp(arr[0], ">"))){
            printf("No command\n");
         }
      else if ( !(strcmp(arr[0], ">>")) || !(strcmp(arr[0], "<<")) ){
            printf("invalid\n");
         }
      
      else {
         //loop through to check which symbol was supplied
         for (int i=1; i < size; i++){
            if (!(strcmp(arr[i], "<"))){
               //input file is at index 0
               input_f = arr[i+1];
               //set option flag to 1
               option = 1;
               //free the symbol from the array
               free(arr[i]);
               //fix array so that there is no empty element
               for(int j = i; arr[j-1] != NULL; j++) 
               {
	               arr[j] = arr[j+2];
               }
            }
            else if (!(strcmp(arr[i], ">"))){
               output_f = arr[i+1];
               option = 0;
               free(arr[i]);
               for(int j = i; arr[j-1] != NULL; j++) 
               {
	               arr[j] = arr[j+2];
               }
            }
            else if (!(strcmp(arr[i], ">>"))){
               outf = arr[i+1];
               option2 = 1;
               free(arr[i]);
               for(int j = i; arr[j-1] != NULL; j++) 
               {
	               arr[j] = arr[j+2];
               }
            }
         }

      }
      //forking
      pid_t pid = fork();
      if (pid < 0)
      {
            printf("error forking\n");
      }
      else if ( (pid == 0) )
      {  
         //if output redirection
         if(option == 0)
         {  
            //open the output file to write
            freopen(output_f, "w+", stdout);
            //exec commands
            execvp(arr[0], arr);
            fclose(stdout);
         }
         //if input redirection
         else if (option==1)
         {  
            //open the input file for reading
            freopen(input_f, "r", stdin);
            execvp(arr[0], arr);
            fclose(stdin);
         }
         if (option2 == 1){
            //open output file for appending
            freopen(outf, "a+", stdout);
            execvp(arr[0], arr);
            fclose(stdout);
         }
         
         if(execvp(arr[0], arr) == -1){
            printf("error");
         }
      }
      else{
         //wait until the child is finished
         waitpid(pid,NULL,0);
      }
      return 0;
}

