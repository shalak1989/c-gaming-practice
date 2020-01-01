# This line will print the shell program being used as make executes
$(info $(SHELL))

CC = gcc
# -g is for debugging, take it out if yhou don't wish to debug or make a separate compile flag
CFLAGS = -Wall -g
LDFLAGS = -lmingw32 -lsdl2main -lsdl2 -mwindows -lSDL2_image -lSDL2_ttf
OBJFILES = status.o main.o
WINDOWS_REMOVE_FILES = status.o, main.o
# For debugging purposes you should make the TARGET equal to the base files exe name, for example main.exe if the file is named main.c
TARGET = main.exe

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm $(OBJFILES) $(TARGET)

# Because you use powershell on windows not all things work correctly. Supposedly the commands are being run from sh.exe according to the command on line 2
clean-windows:
	powershell rm -Force $(WINDOWS_REMOVE_FILES), $(TARGET)
