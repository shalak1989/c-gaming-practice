<!-- 

If your program is compiling but not running try using an external console. Sometimes you won't see any errors with the integrated vscode one.

EXAMPLE:

1. Program was not running, turns out it couldn't find SDL_ttf and a lib file in the %PATH% , C:/mingw/bin or the current working directory
2. All I had to do was either put the files in Mingw's bin or put them in the file locally.
3. All of the files in the base directory you have in this project aren't actually being used, you thought it was working because you had no errors... but really
it was only working due to you having it in C:/mingw/bin which is included in your system path variable (windows).

Leave the files in the base directory alone for now as the test.c file uses some of them. 

If you notice things don't seem to be drawing to the screen correctly, make sure you have a SDL_RenderPresent always getting hit. If its hidden in a conditional you may
have a branch of code that simply never gets drawn.

-->