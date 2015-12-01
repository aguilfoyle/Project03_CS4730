/********************************************************
 *  NAME: Alan Guilfoyle
 *  CLASS: CSCI 4730 - Operating Systems
 *  PROJECT: 03 - File System Simulator
 *
 *  PURPOSE: To implement a simple UNIX-like file system
 *      simulator in order to understand the hierarchical
 *      directory and inode structures.
 *********************************************************/

//---IMPORT(S)---
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "fs.h"
#include "disk.h"



bool command(char * comm, char * comm2)
{
    if( strlen( comm ) == strlen( comm2 ) && strncmp( comm, comm2, strlen( comm )) == 0 )
    {
        return true;
    }
    
    return false;
}

int main(int argc, char ** argv)
{
    //---VARIABLE(S)---
    //  char(s)
    char comm[64];
    char arg1[16];
    char arg2[16];
    char arg3[16];
    char arg4[LARGE_FILE];
    char input[64 + 16 + 16 + 16 + LARGE_FILE];
    
    srand( time( NULL ));
    
    if( argc < 2 )
    {
        fprintf( stderr, "usage: ./fs disk_name\n" );
        
        return -1;
    }
    srand( time( NULL ));
    
    //Call to fs.c file - which will pass file to disk.c to mount
    fs_mount( argv[1] );
    
    //Prints the standard prompt for input
    printf( "%% " );
    
    //The main while loop that will keep the simulator running until
    //  'quit' or 'exit' called
    while( fgets( input, ( MAX_FILE_NAME + SMALL_FILE ), stdin ))
    {
        bzero( comm, 64 );
        bzero( arg1, 16 );
        bzero( arg2, 16 );
        bzero( arg3, 16 );
        bzero( arg4, LARGE_FILE );
        
        int numArg = sscanf( input, "%s %s %s %s %s", comm, arg1, arg2, arg3, arg4 );
        
        if( command( comm, "quit" ) || command( comm, "exit" ))
        {
            break;
        }
        else
        {
            execute_command(comm, arg1, arg2, arg3, arg4, numArg - 1);
        }
        
        printf("%% ");
    }
    
    //Call to fs.c file - which will pass file to disk.c to unmount
    fs_umount(argv[1]);
}