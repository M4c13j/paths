FLAGS = -O1 -Wall -std=c++17 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
CC = g++

FILES := ./src/mesh.hpp ./src/constants.hpp

all: main
	
main:
	$(CC) main.cpp $(FILES) -o main.exe $(FLAGS) 
	echo "everything compiled :D"


# CC = g++
# CCFLAGS = -O1 -Wall -std=c++17 -Wno-missing-braces -I include/ -L lib/ -lraylib -lm -ldl -lrt -lX11
# TARGET = main
# ifeq ($(OS),Windows_NT)
#     CC = g++
#     CCFLAGS = -O1 -Wall -std=c++11 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
# else
#     UNAME_S := $(shell uname -s)
#     ifeq ($(UNAME_S),Linux)
#         CC = g++
#         CCFLAGS = -O1 -Wall -std=c++17 -Wno-missing-braces -I include/ -L lib/ -lraylib -lglfw3 -lGL -lm -pthread -ldl
#         #CCFLAGS = -O1 -Wall -std=c++17 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
#     endif
#     ifeq ($(UNAME_S),Darwin)
#     CC = clang
#         CCFLAGS = -I ./include/raylib.h -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL ./lib/libraylib.a -std=c++17
#     endif
#     # UNAME_P := $(shell uname -p)
#     # ifeq ($(UNAME_P),x86_64)
#     #     CCFLAGS += -D AMD64
#     # endif
#     # ifneq ($(filter %86,$(UNAME_P)),)
#     #     CCFLAGS += -D IA32
#     # endif
#     # ifneq ($(filter arm%,$(UNAME_P)),)
#     #     CCFLAGS += -D ARM
#     # endif
# endif

# FLAGS = -O1 -Wall -std=c++17 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
# main = main.cpp 
# all: main.cpp
# 	g++ ${main} ./src/*.cpp -o main.exe  ${FLAGS}
