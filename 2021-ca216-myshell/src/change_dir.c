/** change_dir.c
 * Author: Caoimhe De Buitlear, 19378783
 * I acknowledge the DCU Academic Integrity Policy: https://www.dcu.ie/sites/default/files/policy/1_-_integrity_and_plagiarism_policy_ovpaa-v4.pdf
 * References: https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

// header files
#include "change_dir.h"

/** Function change_dir
* @params: char array "arr", integer "x"
** description: This function changes the directory to directory specified by the user.
** If no directory is specified, it prints the current working directory. 
**/

int change_dir(char **arr, int x){
   char cwd[1000];
   //if the size of the array is 1 i.e just cd
   if (x == 1){
            //get the current working directory
            getcwd(cwd, sizeof(cwd));
            //print the cwd
            printf("%s\n", cwd);
         }
   else{
      //the directory to change to is at index 1
      //chdir to change directory
      int ch = chdir(arr[1]);
      //if chdir doesn't work then print error
      if (ch<0){
         printf("File not found\n");
      }  
      }
}
