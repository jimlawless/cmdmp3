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
   if(__argc < 2) {
      char msg[64];
      sprintf(msg,"Syntax:\n\tcmdmp3win \"c:\\path to file\\file.mp3\"\n");
      MessageBox(NULL,msg,"cmdmp3win v2.1",MB_OK);
      return 1;
   }

   return PlaySoundFile(__argv[1]);
}
