PROJ_NAME	= DOOM Fire
PROJ_DESC	= Recreating the famous DOOM Fire effect
PROJ_AUTHOR = Andre Zunino <neyzunino@gmail.com>
PROJ_VER	= 0.1.0

UNITS		= fire main
INC_DIR		= include
SRC_DIR		= src
BIN_DIR		= bin
HEADERS     = $(INC_DIR)/fire.hpp
OBJECTS		= $(addprefix $(BIN_DIR)/, $(addsuffix .o, $(UNITS)))
SEIDEL      = seidel-0.12.1
LIBS		= lib/$(SEIDEL).a
EXECUTABLE	= doom-fire-$(PROJ_VER)

SENTRY      = $(BIN_DIR)/sentry
CC			= g++
CFLAGS		= -std=c++2a -c -Wall -g -I$(INC_DIR) -D_REENTRANT
LDFLAGS		= -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_ttf -lSDL2_image

all: $(SENTRY) $(EXECUTABLE)

$(SENTRY):
	@echo Setting things up...
	@mkdir -p bin
	@touch $@

$(EXECUTABLE): $(OBJECTS) $(LIBS)
	$(CC) $(OBJECTS) -o $@ $(LIBS) $(LDFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f bin/*.o
	rm -f $(EXECUTABLE)
	rm -f $(SENTRY)

debug:
	@echo SOURCES: $(SOURCES)
	@echo OBJECTS: $(OBJECTS)
