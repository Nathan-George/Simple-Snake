TARGET = FinalProject
SRC_FILES = main.cpp \
 src/core/Field.cpp src/core/Location.cpp src/core/Snake.cpp src/core/Apple.cpp src/core/SnakeGame.cpp src/core/RandomGenerator.cpp \
 src/graphics/AsciiCanvas.cpp src/graphics/AsciiFunctions.cpp \
 src/sfml_graphics/AppleShape.cpp src/sfml_graphics/FieldShape.cpp src/sfml_graphics/LineShape.cpp src/sfml_graphics/SnakeShape.cpp \
 src/SimpleSnakeBehavior.cpp src/ExampleSnakeBehavior.cpp src/ReplaySnakeBehavior.cpp src/SnakeBehaviorFactory.cpp \
 MainFunctions.cpp MySnakeBehavior.cpp

# NO EDITS NEEDED BELOW THIS LINE

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic-errors
CXXFLAGS_DEBUG = -g
CXXVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(OS),Windows_NT)
	TARGET := $(TARGET).exe
	DEL = del
	Q =

	INC_PATH = Z:/CSCI200/include/
	LIB_PATH = Z:/CSCI200/lib/

	ARCH = 
else
	DEL = rm -f
	Q = "

	INC_PATH = /usr/local/include/
	LIB_PATH = /usr/local/lib/

	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CXXFLAGS += -D LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		TARGET_MAKEFILE = Makefile.osx
		CXXFLAGS += -D OSX
	endif

	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		ARCH = 
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		ARCH = 
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		ARCH = 
	endif
endif

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(ARCH) -o $@ $^ -L$(LIB_PATH) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(ARCH) -o $@ -c $< -I$(INC_PATH)

clean:
	$(DEL) $(TARGET) $(OBJECTS)
	
depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

.PHONY: all clean depend

# DEPENDENCIES
main.o: main.cpp MainFunctions.h
Field.o: src/core/Field.cpp src/core/Field.h src/core/Location.h
Location.o: src/core/Location.cpp src/core/Location.h
Snake.o: src/core/Snake.cpp src/core/Snake.h src/core/SnakeBehavior.h \
 src/core/Field.h src/core/Location.h src/core/Apple.h
Apple.o: src/core/Apple.cpp src/core/Apple.h src/core/Field.h \
 src/core/Location.h src/core/Snake.h src/core/SnakeBehavior.h
SnakeGame.o: src/core/SnakeGame.cpp src/core/SnakeGame.h \
 src/core/SnakeBehavior.h src/core/Snake.h src/core/Location.h \
 src/core/Apple.h src/core/Field.h src/core/RandomGenerator.h
RandomGenerator.o: src/core/RandomGenerator.cpp \
 src/core/RandomGenerator.h
AsciiCanvas.o: src/graphics/AsciiCanvas.cpp src/graphics/AsciiCanvas.h
AsciiFunctions.o: src/graphics/AsciiFunctions.cpp \
 src/graphics/AsciiFunctions.h src/graphics/AsciiCanvas.h \
 src/graphics/../core/SnakeGame.h src/graphics/../core/SnakeBehavior.h \
 src/graphics/../core/Snake.h src/graphics/../core/Location.h \
 src/graphics/../core/Apple.h src/graphics/../core/Field.h \
 src/graphics/../core/RandomGenerator.h
AppleShape.o: src/sfml_graphics/AppleShape.cpp \
 src/sfml_graphics/AppleShape.h src/sfml_graphics/../core/Location.h
FieldShape.o: src/sfml_graphics/FieldShape.cpp \
 src/sfml_graphics/FieldShape.h
LineShape.o: src/sfml_graphics/LineShape.cpp \
 src/sfml_graphics/LineShape.h
SnakeShape.o: src/sfml_graphics/SnakeShape.cpp \
 src/sfml_graphics/SnakeShape.h src/sfml_graphics/../core/Snake.h \
 src/sfml_graphics/../core/SnakeBehavior.h \
 src/sfml_graphics/../core/Snake.h src/sfml_graphics/../core/Field.h \
 src/sfml_graphics/../core/Location.h src/sfml_graphics/../core/Apple.h \
 src/sfml_graphics/LineShape.h
SimpleSnakeBehavior.o: src/SimpleSnakeBehavior.cpp \
 src/SimpleSnakeBehavior.h src/core/SnakeBehavior.h src/core/Snake.h \
 src/core/SnakeBehavior.h src/core/Location.h src/core/Apple.h \
 src/core/Field.h
ExampleSnakeBehavior.o: src/ExampleSnakeBehavior.cpp \
 src/ExampleSnakeBehavior.h src/core/SnakeBehavior.h src/core/Snake.h \
 src/core/SnakeBehavior.h src/core/Location.h src/core/Apple.h \
 src/core/Field.h
ReplaySnakeBehavior.o: src/ReplaySnakeBehavior.cpp \
 src/ReplaySnakeBehavior.h src/core/SnakeBehavior.h src/core/Snake.h \
 src/core/SnakeBehavior.h src/core/Location.h src/core/Apple.h \
 src/core/Field.h
SnakeBehaviorFactory.o: src/SnakeBehaviorFactory.cpp \
 src/SnakeBehaviorFactory.h src/core/SnakeBehavior.h src/core/Snake.h \
 src/core/SnakeBehavior.h src/core/Location.h src/core/Apple.h \
 src/core/Field.h src/SimpleSnakeBehavior.h src/ExampleSnakeBehavior.h \
 src/../MySnakeBehavior.h src/../src/core/SnakeBehavior.h
MainFunctions.o: MainFunctions.cpp MainFunctions.h \
 src/sfml_graphics/SnakeShape.h src/sfml_graphics/../core/Snake.h \
 src/sfml_graphics/../core/SnakeBehavior.h \
 src/sfml_graphics/../core/Snake.h src/sfml_graphics/../core/Field.h \
 src/sfml_graphics/../core/Location.h src/sfml_graphics/../core/Apple.h \
 src/sfml_graphics/AppleShape.h src/sfml_graphics/../core/Location.h \
 src/sfml_graphics/FieldShape.h src/core/SnakeGame.h \
 src/core/SnakeBehavior.h src/core/RandomGenerator.h src/core/Field.h \
 src/core/Apple.h src/core/Snake.h src/graphics/AsciiFunctions.h \
 src/graphics/AsciiCanvas.h src/graphics/../core/SnakeGame.h \
 src/SnakeBehaviorFactory.h src/core/SnakeBehavior.h \
 src/ReplaySnakeBehavior.h MySnakeBehavior.h src/core/SnakeBehavior.h
MySnakeBehavior.o: MySnakeBehavior.cpp MySnakeBehavior.h \
 src/core/SnakeBehavior.h src/core/Snake.h src/core/SnakeBehavior.h \
 src/core/Location.h src/core/Apple.h src/core/Field.h
