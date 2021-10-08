// playsound.c
//
// Contains code that is shared between cmdmp3 and cmdmp3win

#include <windows.h>
#include <stdio.h>
#include <string.h>

void playSoundFile(char *);
void sendCommand(char *);

// Attempt to play the given sound file using Media Control Interface
void playSoundFile(char *fullPath) {
    printf("Playing File: %s\n", fullPath);

    sendCommand("Close All");

    // Dynamically allocate the size cmdBuff based on the true size, instead of guessing
    int bufferSize = snprintf(NULL, 0, "Open %s Type MPEGVideo Alias theMP3", fullPath) + 1;
    char * cmdBuff = malloc(bufferSize);
    snprintf(cmdBuff, bufferSize, "Open %s Type MPEGVideo Alias theMP3", fullPath);
    sendCommand(cmdBuff);

    sendCommand("Play theMP3 Wait");
}

// Send a string to the Media Control Interface
// If an error occurs, display it and the string
// that produced the error.
void sendCommand(char *s) {
    int i = mciSendString(s, NULL, 0, 0);
    if(i) {
        fprintf(stderr, "Error %d when sending %s\n", i, s);
    }
}
