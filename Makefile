# Variable declarations
CC := g++

# Compile flags, use -DSOME_DEFINE to define something ...
CFLAGS := -std=c++11 -Wall -DFMT_HEADER_ONLY

# Additional include directories
CINC_DIR := -I/home/pi/other_src/fmt/include/

# Additional library directories
CLIB_DIR := -L/home/pi/other_src/fmt/

# Add all necessery libs that will be used in the project
# All boost libs are located here: -L/usr/lib/arm-linux-gnueabihf 
CLIBS := -lpthread -lboost_filesystem -lboost_program_options

all: main_prog

main_prog:
	clear
	@echo "Compiling the main ..."
	$(CC) $(CINC_DIR) $(CLIB_DIR) $(CFLAGS) $(CLIBS) -o main.out main.cpp

clean:
	rm -rf *.o main