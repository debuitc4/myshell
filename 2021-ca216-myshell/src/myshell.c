/** myshell.c
 * Author: Caoimhe De Buitlear, 19378783
 * I acknowledge the DCU Academic Integrity Policy: https://www.dcu.ie/sites/default/files/policy/1_-_integrity_and_plagiarism_policy_ovpaa-v4.pdf
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include<sys/wait.h> 

//header files
#include "io_redirection.h"
#include "change_dir.h"
#include "input_from_file.h"
#include "help.h"
#include "makerm_dir.h"

#define MAX_SIZE 1025

int main(int argc, char *argv[],  char *envp[]){
   char args[100];
   char *word;
   char cpy[100];

   //seting the shell environment varible
   char fullpath[1024];
   //getting current working dir
   getcwd(fullpath, 1024);
   setenv("SHELL", fullpath, 1);

   //reading input from batchfile
   if(argc > 1) {
      char *filename = argv[1];
      //checking if the file exists
      if (access(filename, F_OK) ==0){
         input_from_file(filename);
      }
      else{
         printf("File does not exist.\n");
      }
      //once commands are executed, exit
      exit(0);
   }

   //starting shell prompt
   while(1){
      char** cmdArgs = (char **)malloc(100 * sizeof(char));
      //print prompt with colour
      printf("\e[0;35m %s/myshell >> \e[0;35m", fullpath);
      //getting arguments
      fgets(args, MAX_SIZE, stdin);
      strcpy(cpy, args);

      //breaking up the arguments into array
      word = strtok(args, " ");
      int i=0;
      while( word != NULL )
      { 
         cmdArgs[i] = strdup(word);
         word = strtok(NULL, " ");
         i++;
      }
       //if quit is entered then quit program
      if (!strcmp(cmdArgs[0], "quit")){
         exit(0);
      }
      //removing newline character from last element of the array
      cmdArgs[i-1][strcspn(cmdArgs[i-1], "\n")] = 0;

      //looking for input/output signs, if found go to io_direction file
      if (strchr(cpy, '<') != NULL || strchr(cpy, '>') != NULL){
         io_redirection(cmdArgs, i);
      }
      //checking for ampersand
      else if ( strchr(cpy, '&') != NULL){
         //replacing ampersand with NULL
         cmdArgs[argc-1] = NULL;
         //forking the process
         pid_t p = fork();
         if (p < 0)
         {
            printf("error\n");
         }
         else if ( (p == 0) )
         {  
            //execute commands in the background
            execvp(cmdArgs[0], cmdArgs);
         }
         
      }

      //makes directory or removes directory
      else if(!strcmp(cmdArgs[0], "mkdir") || !strcmp(cmdArgs[0], "rmdir")){
         makerm_dir(cmdArgs, i);
      }

      //changing directory
      else if (!strcmp(cmdArgs[0], "cd")){
         change_dir(cmdArgs, i);
         getcwd(fullpath, 1024);
      }
      
      //clearing the screen
      else if (!strcmp(cmdArgs[0], "clr")){
         system("clear");
      }
      //listing all files in current directory
      else if (!strcmp(cmdArgs[0], "dir")){
         system("ls -a");
      }
      //listing all environment variables
      else if (!strcmp(cmdArgs[0], "environ")){
         int i = 0;
         while(envp[i] != NULL){
            printf("%s\n", envp[i]);
            i++;
         }
      }
      //echos the commands supplied after it, removing excessive tabs/spaces
      else if (!strcmp(cmdArgs[0], "echo"))
      {  
         for (int v=0; v<i; v++)
         {
            for(int y=0; y<strlen(cmdArgs[v]); y++){
               if (cmdArgs[v][y] == '\t'){
                  cmdArgs[v][y] = ' ';
               }
            }
         }
         for(int v=1;v<i;v++){
            printf("%s ", cmdArgs[v]);
         }
         printf("\n");
      }
      //displays the user manual (with more filter applied)
      else if (!strcmp(cmdArgs[0], "help"))
      {     
         help();
      }
      //pauses the porgram until enter is pressed
      else if (!strcmp(cmdArgs[0], "pause"))
      {
         printf("press enter to continue.");
         getchar();
      }
      //quits the program
      else if (!strcmp(cmdArgs[0], "quit"))
      {
         exit(0);
      }

      //if no input supplied then display prompt
      else if (strlen(cmdArgs[0]) < 1)
      {
         ;
      }

      //if none of the commands are recognised, fork and execute external commands.
      else if (strlen(cmdArgs[0]) >= 1)
      {
         //forking the process
         pid_t pid = fork();
         if (pid < 0)
         {
               printf("error\n");
         }
         else if ( (pid == 0) )
         {
            if (i == 1)
            {  
               //if its a single command use execlp
               execlp("/bin/sh", "/bin/sh", "-c", cmdArgs[0], NULL);
            }
            else
            {  
               //append command to /bin/ then use exev to execute
               char str[100];
               strcat(str, "/bin/");
               strcat(str, cmdArgs[0]);
               execv(str, cmdArgs);
               printf("execv failed\n");
               exit(0);
            }
         }
         else
         {
            //parent waiting on child to finish
            wait(NULL);
         }
   }
      //freeing the array cmdArgs
      free(cmdArgs);
}
   return 0;

}