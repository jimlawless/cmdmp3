all: cmdmp3 cmdmp3win

cmdmp3: cmdmp3.c
	gcc -o cmdmp3.exe cmdmp3.c -l Winmm
    
cmdmp3win: cmdmp3win.c
	gcc -o cmdmp3win.exe cmdmp3win.c -l Winmm -mwindows

clean: 
	rm cmdmp3.exe
	rm cmdmp3win.exe