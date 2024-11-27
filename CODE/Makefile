#=================================================================================
# Makefile for SLAC.  Requires the following:
# - A functional installation of DJGPP
# - A copy of Allegro
#
# In my case, I'm using very particular retro versions:
# - gcc 2.95.2
# - Allegro 3.0
#
# Your mileage may vary if you use later versions of DJGPP and/or Allegro.
# Replacing the former is possibly OK, the latter probably not.
#
# Also note - this Makefile requires that rm.exe (from the DJGPP fileutils package)
# be installed.  This isn't normally a required package for a functional DJGPP
# distribution, but the package is available in the v2gnu/ directory.
#==================================================================================
CC=gpp
CFLAGS=-O2 -Iinc
LIBS=-lalleg -lm

TARGET=slac.exe
OBJS=obj/gen_data.o obj/utils.o obj/textlog.o obj/maze.o obj/render.o obj/player.o obj/invntory.o obj/itemgen.o obj/input.o obj/main.o 

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)
	
prod: $(TARGET) 
	strip $(TARGET)
	upx $(TARGET)

obj/utils.o: src/utils.cpp 
	$(CC) -c $(CFLAGS) -o obj/utils.o src/utils.cpp

obj/input.o: src/input.cpp inc/input.h 
	$(CC) -c $(CFLAGS) -o obj/input.o src/input.cpp

obj/itemgen.o: src/itemgen.cpp inc/itemgen.h inc/invntory.h
	$(CC) -c $(CFLAGS) -o obj/itemgen.o src/itemgen.cpp

obj/gen_data.o: src/gen_data.cpp inc/gen_data.h
	$(CC) -c $(CFLAGS) -o obj/gen_data.o src/gen_data.cpp

obj/textlog.o: src/textlog.cpp inc/textlog.h
	$(CC) -c $(CFLAGS) -o obj/textlog.o src/textlog.cpp

obj/maze.o: src/maze.cpp inc/maze.h
	$(CC) -c $(CFLAGS) -o obj/maze.o src/maze.cpp

obj/render.o: src/render.cpp inc/render.h inc/globals.h inc/maze.h inc/textlog.h inc/utils.h
	$(CC) -c $(CFLAGS) -o obj/render.o src/render.cpp

obj/player.o: src/player.cpp inc/player.h inc/invntory.h
	$(CC) -c $(CFLAGS) -o obj/player.o src/player.cpp

obj/invntory.o: src/invntory.cpp inc/invntory.h inc/invntory.h inc/gen_data.h
	$(CC) -c $(CFLAGS) -o obj/invntory.o src/invntory.cpp

obj/main.o: src/main.cpp inc/main.h inc/utils.h inc/render.h inc/player.h inc/maze.h inc/invntory.h inc/itemgen.h
	$(CC) -c $(CFLAGS) -o obj/main.o src/main.cpp
	
clean:
	@echo Removing files...
	@rm -f obj/*.o
	@rm -f $(TARGET)
	