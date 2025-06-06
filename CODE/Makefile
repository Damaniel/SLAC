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

# The default is to build with 386-specific instructions.  If running on an emulator
# target (i.e. DOSBox), building with HIGH_END set will enable Pentium-specific
# instructions.  Standard builds will include (for now) softfloat support - eventually,
# fixed point code will be dropped in as a replacement.
ifdef HIGH_END
ARCH=-march=pentium
EMU=
else
ARCH=-march=i386
EMU=-lemu
endif

CFLAGS=-O2 -Iinc $(ARCH)
LIBS=-lalleg -lm $(EMU)
TARGET=slac.exe

OBJS=obj/gen_data.o obj/tiledata.o obj/utils.o obj/town.o obj/textlog.o obj/maze.o obj/render.o obj/t_cache.o obj/player.o obj/enemy.o obj/saveload.o obj/invntory.o obj/itemgen.o obj/item_use.o obj/input.o obj/main.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

prod: $(TARGET)
	strip $(TARGET)
	upx $(TARGET)

obj/utils.o: src/utils.cpp inc/globals.h
	$(CC) -c $(CFLAGS) -o obj/utils.o src/utils.cpp

obj/saveload.o: src/saveload.cpp inc/globals.h
	$(CC) -c $(CFLAGS) -o obj/saveload.o src/saveload.cpp

obj/town.o: src/town.cpp inc/town.h
	$(CC) -c $(CFLAGS) -o obj/town.o src/town.cpp

obj/t_cache.o: src/t_cache.cpp inc/t_cache.h inc/render.h
	$(CC) -c $(CFLAGS) -o obj/t_cache.o src/t_cache.cpp

obj/input.o: src/input.cpp inc/input.h
	$(CC) -c $(CFLAGS) -o obj/input.o src/input.cpp

obj/itemgen.o: src/itemgen.cpp inc/itemgen.h inc/invntory.h
	$(CC) -c $(CFLAGS) -o obj/itemgen.o src/itemgen.cpp

obj/item_use.o: src/item_use.cpp inc/itemgen.h inc/invntory.h inc/item_use.h
	$(CC) -c $(CFLAGS) -o obj/item_use.o src/item_use.cpp

obj/gen_data.o: src/gen_data.cpp inc/gen_data.h
	$(CC) -c $(CFLAGS) -o obj/gen_data.o src/gen_data.cpp

obj/tiledata.o: src/tiledata.cpp
	$(CC) -c $(CFLAGS) -o obj/tiledata.o src/tiledata.cpp

obj/textlog.o: src/textlog.cpp inc/textlog.h
	$(CC) -c $(CFLAGS) -o obj/textlog.o src/textlog.cpp

obj/maze.o: src/maze.cpp inc/maze.h
	$(CC) -c $(CFLAGS) -o obj/maze.o src/maze.cpp

obj/render.o: src/render.cpp inc/render.h inc/globals.h inc/maze.h inc/textlog.h inc/utils.h
	$(CC) -c $(CFLAGS) -o obj/render.o src/render.cpp

obj/player.o: src/player.cpp inc/player.h inc/invntory.h
	$(CC) -c $(CFLAGS) -o obj/player.o src/player.cpp

obj/enemy.o: src/enemy.cpp inc/enemy.h
	$(CC) -c $(CFLAGS) -o obj/enemy.o src/enemy.cpp

obj/invntory.o: src/invntory.cpp inc/invntory.h inc/invntory.h inc/gen_data.h
	$(CC) -c $(CFLAGS) -o obj/invntory.o src/invntory.cpp

obj/main.o: src/main.cpp inc/main.h inc/utils.h inc/render.h inc/player.h inc/maze.h inc/invntory.h inc/itemgen.h
	$(CC) -c $(CFLAGS) -o obj/main.o src/main.cpp

clean:
	@echo Removing files...
	@rm -f obj/*.o
	@rm -f $(TARGET)
