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



PCHAR* CommandLineToArgvA(PCHAR, int*);

int WINAPI WinMain( HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow ) {

   char shortBuffer[MAX_PATH];
   char msg[256];

   char ** arguments;
   int numberOfArguments;
   arguments = CommandLineToArgvA(GetCommandLine(), &numberOfArguments);

   if(numberOfArguments < 2) {
      sprintf(msg,"Syntax:\n\tcmdmp3win \"c:\\path to file\\file.mp3\"\n");
      MessageBox(NULL,msg,"cmdmp3win v2.0",MB_OK);
      return 1;
   }

   // Get the shortened path because the MCI string interpreter uses spaces
   // as a separator. If spaces appear in the commands, parts of the filename
   // would be interpreted as parameters to the given command.
   GetShortPathName(arguments[1], shortBuffer, sizeof(shortBuffer));
   if(!*shortBuffer) {
      sprintf(msg,"Cannot shorten filename \"%s\"\n",arguments[1]);
      MessageBox(NULL,msg,"cmdmp3win",MB_OK);
      return 1;
   }

   playSoundFile(shortBuffer);
   return 0;
}

PCHAR* CommandLineToArgvA(PCHAR CmdLine, int* _argc) {
   PCHAR* argv;
   PCHAR  _argv;
   ULONG   len;
   ULONG   argc;
   CHAR   a;
   ULONG   i, j;

   BOOLEAN  in_QM;
   BOOLEAN  in_TEXT;
   BOOLEAN  in_SPACE;

   len = strlen(CmdLine);
   i = ((len+2)/2)*sizeof(PVOID) + sizeof(PVOID);

   argv = (PCHAR*)GlobalAlloc(GMEM_FIXED,
                              i + (len+2)*sizeof(CHAR));

   _argv = (PCHAR)(((PUCHAR)argv)+i);

   argc = 0;
   argv[argc] = _argv;
   in_QM = FALSE;
   in_TEXT = FALSE;
   in_SPACE = TRUE;
   i = 0;
   j = 0;

   while( a = CmdLine[i] ) {
      if(in_QM) {
         if(a == '\"') {
            in_QM = FALSE;
         } else {
            _argv[j] = a;
            j++;
         }
      } else {
         switch(a) {
            case '\"':
               in_QM = TRUE;
                 in_TEXT = TRUE;
                 if(in_SPACE) {
                    argv[argc] = _argv+j;
                    argc++;
                 }
                 in_SPACE = FALSE;
                 break;
            case ' ':
            case '\t':
            case '\n':
            case '\r':
               if(in_TEXT) {
                  _argv[j] = '\0';
                  j++;
               }
                 in_TEXT = FALSE;
                 in_SPACE = TRUE;
                 break;
            default:
               in_TEXT = TRUE;
                 if(in_SPACE) {
                    argv[argc] = _argv+j;
                    argc++;
                 }
                 _argv[j] = a;
                 j++;
                 in_SPACE = FALSE;
                 break;
         }
      }
      i++;
   }
   _argv[j] = '\0';
   argv[argc] = NULL;

   (*_argc) = argc;
   return argv;
}