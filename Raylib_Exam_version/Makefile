BUILD_MODE ?= RELEASE

DEPS = Cube.h Object.h ModelObject.h GPU.h ParticleSystem.h Effect.h Gravity.h Plan.h Collider.h Force.h Sphere.h
OBJ = main.o Object.o Cube.o ModelObject.o GPU.o ParticleSystem.o Gravity.o Plan.o Sphere.o


PLATFORM_OS=BSD
ifeq ($(OS),Windows_NT)
	PLATFORM_OS=WINDOWS
	RAYLIB=C:/raylib/raylib
	CC=C:/raylib/mingw/bin/g++
	LIBS=-L$(RAYLIB)/src -lraylib -lopengl32 -lgdi32 -lwinmm C:/raylib/raylib/src/raylib.rc.data
else
	UNAMEOS=$(shell uname)
	ifeq ($(UNAMEOS),Darwin)
		PLATFORM_OS=OSX
		RAYLIB=raylib
		CC=clang++
		LIBS=$(RAYLIB)/src/libraylib.a -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -framework OpenCL
	endif
	ifeq ($(UNAMEOS),Linux)
		# Not Tested !!
		PLATFORM_OS=LINUX
		CC=g++
		LIBS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
		#For Wayland
		#LIBS += -lwayland-client -lwayland-cursor -lwayland-egl -lxkbcommon
	endif
endif

INCLUDES=-I$(RAYLIB)/src -I$(RAYLIB)/src/external
CFLAGS=-Wall -Wno-missing-braces -std=c++17

ifeq ($(BUILD_MODE),DEBUG)
	CFLAGS += -g -O0
else
	CFLAGS += -O3
endif

all: app

app: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

libraylib:
	$(MAKE) -C raylib/src all

cleanraylib:
	$(MAKE) -C raylib/src clean

clean:
	rm -f *.o

mrproper: clean
	rm -f app
