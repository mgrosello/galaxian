####
	#makefile for rblocks.
	#Copyright (C) 2015 Adam Richardson

	#This program is free software: you can redistribute it and/or modify
	#it under the terms of the GNU General Public License as published by
	#the Free Software Foundation, either version 3 of the License, or
	#(at your option) any later version.

	#This program is distributed in the hope that it will be useful,
	#but WITHOUT ANY WARRANTY; without even the implied warranty of
	#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	#GNU General Public License for more details.

	#You should have received a copy of the GNU General Public License
	#along with this program.  If not, see <http://www.gnu.org/licenses/>.
####

CC = emcc
SOURCE = main.c game.c video.c nap.c common.c font.c icon.c
BUILD = build
OBJECTS = $(addprefix $(BUILD)/,$(SOURCE:.c=.o)) 
OUTPUT = rblocks
CFLAGS = -Wall -Wextra -Werror -O3 -std=c99 -pedantic -ggdb  -s USE_SDL=2  # `sdl2-config --cflags --libs`

.PHONY: all
.PHONY: clean

all: $(BUILD)/$(OUTPUT)

$(BUILD)/$(OUTPUT): $(OBJECTS)
	$(CC) -o $(BUILD)/$(OUTPUT) $(addprefix ,$(OBJECTS)) $(CFLAGS)

#Object files are built from .c files; a change in the correspending header is equally important
$(BUILD)/%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<	

#$(BUILD)/%.o: %.c %.h
#	$(CC) $(CFLAGS) -o $@ -c $< asdasdasd
$(BUILD)/font.o: font.c font.h fontdef.h
	$(CC) $(CFLAGS) -c font.c -o $@

#fontdef.h is special also
fontdef.h: fontdef.txt fontgen.py
	python fontgen.py < fontdef.txt > fontdef.h

#Nuke everything, don't die on error
clean:
	-rm $(OUTPUT) $(OBJECTS) fontdef.h
