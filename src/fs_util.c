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
#include <stdlib.h>
#include <time.h>
#include "fs.h"



/**
 * Method: Creates random number of chars for string
 *
 * @param: char *str - The string to manipulate
 * @param: size_t size - The size of string
 *
 * Returns:
 *      The size of newly generated string
 */
int rand_string( char * str, size_t size)
{
    if(size < 1)
        return 0;
    
    int n, key;
    
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    
    for (n = 0; n < size; n++)
    {
        key = rand() % (int) (sizeof charset - 1);
        str[n] = charset[key];
    }
    str[size] = '\0';
    
    return size + 1;
}



/**
 * Method:
 *
 * @param: char * array - 
 * @param: int index -
 *
 * RETURNS:
 *      None
 */
void toggle_bit( char * array, int index )
{
    array[index/8] ^= 1 << ( index % 8 );
}



/**
 * Method:
 *
 * @param: char * array -
 * @param: int index -
 *
 * Returns: char
 */
char get_bit( char * array, int index )
{
    return 1 & ( array[index/8] >> ( index % 8 ));
}



/**
 * Method:
 *
 * @param: char * array -
 * @param: int index -
 * @param: char value -
 *
 * Returns: None
 */
void set_bit( char * array, int index, char value )
{
    if( value != 0 && value != 1 )
    {
        return;
    }
    
    //printf( "SET BIT %d\n", array[index/8] ^= 1 << ( index % 8 ));
    array[index/8] ^= 1 << ( index % 8 );
    
    if( get_bit( array, index ) == value)
    {
        return;
    }
    
    toggle_bit( array, index );
}



/*
 * Method: Checks for a free inode and then returns it if
 *  there is one
 *
 * PARAMETERS: None
 *
 * Returns: int
 *
 */
int get_free_inode()
{
    int i = 0;
    
    for( i = 0; i < MAX_INODE; i++ )
    {
        if( get_bit( inodeMap, i ) == 0)
        {            
            set_bit( inodeMap, i, 1 );
            
            superBlock.freeInodeCount--;
            
            return i;
        }
    }
    
    return -1;
}



/**
 * Method: looks for a free block; returns block number
 *  if there is one
 *
 * @param: None
 *
 * Returns: int
 *
 */
int get_free_block()
{
    int i = 0;
    
    for( i = 0; i < MAX_BLOCK; i++ )
    {
        if( get_bit( blockMap, i ) == 0 )
        {
            set_bit( blockMap, i, 1 );
            superBlock.freeBlockCount--;
            
            return i;
        }
    }
    
    return -1;
}



/*
 * Method: Sets / formats the correct time by retriving the system time
 *
 * @param: struct timeval * tv -
 * @param: char * buf -
 * @param: size_t sz -
 *
 * Returns: The size of newly generated string
 */
int format_timeval( struct timeval * tv, char * buf, size_t sz )
{
    ssize_t written = -1;
    struct tm * gm;
    gm = gmtime( &tv -> tv_sec );
    
    if( gm )
    {
        written = ( ssize_t )strftime( buf, sz, "%Y-%m-%d %H:%M:%S", gm );
        
        if(( written > 0 ) && (( size_t )written < sz ))
        {
            int w = snprintf( buf + written, sz - ( size_t )written, ".%06dZ", tv -> tv_usec );
            written = (w > 0) ? written + w : -1;
        }
    }
    
    return written;
}