/********************************************************
 *  NAME: Alan Guilfoyle
 *  CLASS: CSCI 4730 - Operating Systems
 *  PROJECT: 03 - File System Simulator
 *
 *  PURPOSE: To implement a simple UNIX-like file system
 *      simulator in order to understand the hierarchical
 *      directory and inode structures.
 *********************************************************/

//---DEFINITION(S)---
#define BLOCK_SIZE 512
#define MAX_BLOCK 4096

//---GLOBAL VARIABLE(S)
extern char disk[MAX_BLOCK][BLOCK_SIZE];

//---METHOD INSTANTIATION(S)---
int disk_read( int block, char * buf );
int disk_write( int block, char * buf );
int disk_mount( char * name );
int disk_umount( char * name );