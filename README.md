# cmdmp3 [![CodeQL](https://github.com/A9G-Data-Droid/cmdmp3/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/A9G-Data-Droid/cmdmp3/actions/workflows/codeql-analysis.yml)

Lightweight command-line MP3 players for Windows written in C 

I've had to rebuild these files since their initial release.  Please see the blog post at:

https://lawlessguy.wordpress.com/2015/06/27/update-to-a-command-line-mp3-player-for-windows/

To build, use the following MinGW command:

```
gcc -o cmdmp3.exe cmdmp3.c -l Winmm
gcc -o cmdmp3win.exe cmdmp3win.c -l Winmm -mwindows
```
