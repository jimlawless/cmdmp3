// cmdmp3
// A command-line MP3 player for Windows
// (console-mode version)
//
// License: MIT / X11
// Copyright (c) 2009, 2015 by James K. Lawless
// jimbo@radiks.net  http://jiml.us
// See http://www.mailsend-online.com/license2015.php
//
// To build, use the following MinGW command:
//    gcc -o cmdmp3.exe cmdmp3.c -l Winmm

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "playsound.c"



int main(int argc, char **argv) {
   char shortBuffer[MAX_PATH];
   printf("cmdmp3 v2.1\n");
   printf("Command-line MP3 player\n");
   printf("by Jim Lawless - https://jiml.us\n\n");

   if(argc<2) {
      printf("\n");
      fprintf(stderr, "Syntax:\n\tcmdmp3 \"c:\\path to file\\file.mp3\"\n");
      return 1;
   }

   // Get the shortened path because the MCI string interpreter uses spaces
   // as a separator. If spaces appear in the commands, parts of the filename
   // would be interpreted as parameters to the given command.
   GetShortPathName(argv[1], shortBuffer, sizeof(shortBuffer));
   if(!*shortBuffer) {
      fprintf(stderr, "Cannot shorten filename \"%s\"\n", argv[1]);
      return 1;
   }

   playSoundFile(shortBuffer);
   return 0;
}