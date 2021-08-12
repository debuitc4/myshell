/** help.c
 * Author: Caoimhe De Buitlear, 19378783
 * I acknowledge the DCU Academic Integrity Policy: https://www.dcu.ie/sites/default/files/policy/1_-_integrity_and_plagiarism_policy_ovpaa-v4.pdf
*/

#include <unistd.h>
#include <stdio.h>

// header files
#include "help.h"

/** Function help
* @params: none
** description: This function displays the readme manual, with the more filter.
**/

int help(){
   //changes into the dir that the manual is in
   chdir("..");
   chdir("manual");
   //executes the manual with the more filter
   char * a[3];
   a[0] = "more";
   a[1] = "readme";
   a[2] = NULL;
   execvp(a[0], a);


   //changes back to the src dir
   chdir("..");
   chdir("src");
}