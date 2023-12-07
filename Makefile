TARGET = FinalProject
SRC_FILES = main.cpp \
 src/core/Field.cpp src/core/Location.cpp src/core/Snake.cpp src/core/Apple.cpp src/core/SnakeGame.cpp src/core/RandomGenerator.cpp \
 src/graphics/AsciiCanvas.cpp src/graphics/AsciiFunctions.cpp src/graphics/SnakeGraphics.cpp \
 src/SimpleSnakeBehavior.cpp src/ExampleSnakeBehavior.cpp src/ReplaySnakeBehavior.cpp src/SnakeBehaviorFactory.cpp \
 MySnakeBehavior.cpp

# NO EDITS NEEDED BELOW THIS LINE

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic-errors
CXXFLAGS_DEBUG = -g
CXXVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = del
	Q =
else
	DEL = rm -f
	Q = "
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

.cpp.o:
	$(CXX) $(CXXFLAGS) $(CXXVERSION) $(CXXFLAGS_DEBUG) -o $@ -c $<

clean:
	$(DEL) $(TARGET) $(OBJECTS)

depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

.PHONY: all clean depend

# DEPENDENCIES
main.o: main.cpp src/core/SnakeGame.h src/core/SnakeBehavior.h \
 src/core/Snake.h src/core/Location.h src/core/Apple.h src/core/Field.h \
 src/core/RandomGenerator.h src/graphics/AsciiFunctions.h \
 src/graphics/AsciiCanvas.h src/graphics/../core/SnakeGame.h \
 src/SnakeBehaviorFactory.h src/core/SnakeBehavior.h \
 src/ReplaySnakeBehavior.h MySnakeBehavior.h src/core/SnakeBehavior.h
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
SnakeGraphics.o: src/graphics/SnakeGraphics.cpp
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
MySnakeBehavior.o: MySnakeBehavior.cpp MySnakeBehavior.h \
 src/core/SnakeBehavior.h src/core/Snake.h src/core/SnakeBehavior.h \
 src/core/Location.h src/core/Apple.h src/core/Field.h
