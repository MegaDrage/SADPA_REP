CFLAGS= -Wall -Werror -Wextra -g
CC=g++
CSDIR=CourseWork/src/
SRC=$(CSDIR)main.cpp $(CSDIR)list.cpp $(CSDIR)database.cpp $(CSDIR)record.cpp
SRC0 = lab0/main.cpp lab0/libs.cpp
SRC1 = lab1/main.cpp lab1/libs.hpp
SRC1 = lab2/main.cpp lab2/libs.hpp
OBJS=$(SRC:.c=.o)
OBJS0=$(SRC0:.c=.o)
OBJS1=$(SRC1:.c=.o)
OBJS2=$(SRC2:.c=.o)
CODIR=CourseWork/build/
ODIR=build/
TARGET=$(ODIR)CS_Work.exe
TARGET0=$(ODIR)lab0.exe
TARGET1=$(ODIR)lab1.exe
TARGET1=$(ODIR)lab2.exe
LIBS=-lm

.PHONY: CS_Work lab0 lab1 lab2 all clean clean_all
all: CS_Work lab0 lab1 lab2 clean
CS_Work: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)
lab0: $(TARGET0)
$(TARGET0): $(OBJS0)
	$(CC) $(CFLAGS) -o $@ $(OBJS0) $(LIBS)
lab1: $(TARGET1)
$(TARGET1): $(OBJS1)
	$(CC) $(CFLAGS) -o $@ $(OBJS1) $(LIBS)
lab2: $(TARGET2)
$(TARGET2): $(OBJS2)
	$(CC) $(CFLAGS) -o $@ $(OBJS2) $(LIBS)
clean:
	find ../ -name "*.o" -type f -delete
clean_all: clean
	find ../build/ -name "*.exe" -type f -delete
