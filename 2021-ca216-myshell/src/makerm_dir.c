/** makerm_dir.c
 * Author: Caoimhe De Buitlear, 19378783
 * I acknowledge the DCU Academic Integrity Policy: https://www.dcu.ie/sites/default/files/policy/1_-_integrity_and_plagiarism_policy_ovpaa-v4.pdf
 * References: https://stackoverflow.com/questions/5467725/how-to-delete-a-directory-and-its-contents-in-posix-c
 * 
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

// header files
#include "makerm_dir.h"

/** Function makerm_dir
* @params: char array "arr", integer "x"
** description: This function creates or deletes a directory
** based off what the user inputs, under the name the user inputs. 
**/

int makerm_dir(char **arr, int x){
     
     //checks if there is a directory name
     if (x < 2){
        printf("no directory name inputted\n");
     }
     else{
        //checks if the command is mkdir
        if (!strcmp(arr[0], "mkdir")){
            //checks if the directory already exists
            if (access(arr[1], F_OK) == 0){
                  printf("Directory already exists\n");
            }
            //if it doesn't exist then it creates the directory
            else{
               mkdir(arr[1], 0700);
            }
        }
       //checks if the command is rmdir 
       else if (!strcmp(arr[0], "rmdir")){
          //removes it
          int rm = remove(arr[1]);
          //if remove didnt work then print error
          if(rm){
             perror(arr[1]);
          }
       }
     }
      return 0;
}
