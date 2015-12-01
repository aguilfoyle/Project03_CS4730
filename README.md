# Project 03 - UNIX-like File System Simulator

## Description

In this project, you will implement a simple UNIX-like file system simulator in order to understand the hierarchical 
directory and inode structures. You will be able to (1) browse the disk information, file and directory list, (2) 
create and delete files and directories, (3) read and write files. The functionality of the file system is similar 
to UNIX file systems, but it does not include per-process open file table, permission and user management. 

## Part 1: Small size files

Implemented: create, cat, read, and write

## Part 2: Directory

Implemented: mkdir, rmdir, and chdir

## How to run:

To run the program you can run the MAKEFILE by using the 'make' command. It will compile 7 files:
disk.c, disk.h, fs.c, fs.h, fs_sim.c, fs_util.c, fs_util.h

After compling simply use the command: ./fs_sim ANY_FILE_NAME 
this will create a new 'disk' file and mount it and start the program.
