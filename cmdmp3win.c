// cmdmp3win
// A command-line MP3 player for Windows
// (window-mode version)
//
// License: MIT / X11
// Copyright (c) 2009, 2015 by James K. Lawless
// jimbo@radiks.net  http://jiml.us
// See http://www.mailsend-online.com/license2015.php
//
// To build, use the following MinGW command:
//   gcc -o cmdmp3win.exe cmdmp3win.c -l Winmm -mwindows

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "playsound.c"



extern int __argc;
extern char ** __argv;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {

   char shortBuffer[MAX_PATH];
   char msg[256];

   if(__argc < 2) {
      sprintf(msg,"Syntax:\n\tcmdmp3win \"c:\\path to file\\file.mp3\"\n");
      MessageBox(NULL,msg,"cmdmp3win v2.0",MB_OK);
      return 1;
   }

   // Get the shortened path because the MCI string interpreter uses spaces
   // as a separator. If spaces appear in the commands, parts of the filename
   // would be interpreted as parameters to the given command.
   GetShortPathName(__argv[1], shortBuffer, sizeof(shortBuffer));
   if(!*shortBuffer) {
      sprintf(msg,"Cannot shorten filename \"%s\"\n",__argv[1]);
      MessageBox(NULL,msg,"cmdmp3win",MB_OK);
      return 1;
   }

   playSoundFile(shortBuffer);
   return 0;
}
