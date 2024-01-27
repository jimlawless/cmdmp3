// cmdmp3
// A command-line MP3 player for Windows
// (console-mode version)
//
// License: MIT / X11
// Copyright (c) 2009, 2015, 2022-2024 by James K. Lawless
// jimbo@radiks.net  http://jiml.us
// See https://jiml.us/license2022.htm
//
// To build, use the following MinGW command:
//    gcc  cmdmp3.c -lwinmm   -o cmdmp3.exe

#include <windows.h>
#include <stdio.h>
#include <string.h>

void sendCommand(char *);

int main(int argc,char **argv) {
    char cmdBuff[MAX_PATH + 64];
    printf("cmdmp3 v2.30\n");
    printf("Command-line MP3 player\n");
    printf("by Jim Lawless - https://jiml.us\n");
   
    if(argc<2) {
        fprintf(stderr,"Syntax:\n\tcmdmp3 \"c:\\path to file\\file.mp3\"\n\t   or\n\tcmdmp3 \"url\"\n\n");
        return 1;
    }
    sendCommand("Close All");

    sprintf(cmdBuff,"Open \"%s\" Type MPEGVideo Alias theMP3",argv[1]);
    sendCommand(cmdBuff);

    sendCommand("Play theMP3 Wait");
    return 0;
}

    // Send a string to the Media Control Interface
    // If an error occurs, display it and the string
    // that produced the error.
void sendCommand(char *s) {
    int i;
    i=mciSendString(s,NULL,0,0);
    if(i) {
        fprintf(stderr,"Error %d when sending %s\n",i,s);
   }
}
