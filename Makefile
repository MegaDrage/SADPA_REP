CFLAGS= -Wall -Werror -Wextra -g `sdl2-config --cflags`
CC=g++
CSDIR=CourseWork/src/
SRC=$(CSDIR)main.cpp $(CSDIR)list.cpp $(CSDIR)database.cpp $(CSDIR)record.cpp $(CSDIR)treeFuncs.cpp
SRC0 = lab0/main.cpp lab0/libs.cpp
SRC1 = lab1/main.cpp lab1/libs.hpp
SRC2 = lab2/main.cpp lab2/libs.hpp
SRC3 = lab3/main.cpp lab3/libs.hpp
SRC4 = lab4/main.cpp lab4/libs.hpp
SRC5 = lab5/main.cpp lab5/libs.hpp
SRC6 = lab6/main.cpp lab6/libs.hpp
SRC7 = lab7/main.cpp lab7/libs.hpp
SRC8 = lab8/main.cpp lab8/libs.hpp
OBJS=$(SRC:.c=.o)
OBJS0=$(SRC0:.c=.o)
OBJS1=$(SRC1:.c=.o)
OBJS2=$(SRC2:.c=.o)
OBJS3=$(SRC3:.c=.o)
OBJS4=$(SRC4:.c=.o)
OBJS5=$(SRC5:.c=.o)
OBJS6=$(SRC6:.c=.o)
OBJS7=$(SRC7:.c=.o)
OBJS8=$(SRC8:.c=.o)
CODIR=CourseWork/build/
ODIR=build/
TARGET=$(ODIR)CS_Work.exe
TARGET0=$(ODIR)lab0.exe
TARGET1=$(ODIR)lab1.exe
TARGET2=$(ODIR)lab2.exe
TARGET3=$(ODIR)lab3.exe
TARGET4=$(ODIR)lab4.exe
TARGET5=$(ODIR)lab5.exe
TARGET6=$(ODIR)lab6.exe
TARGET7=$(ODIR)lab7.exe
TARGET8=$(ODIR)lab8.exe
LIBS=-lm `sdl2-config --libs` -lSDL2_gfx

.PHONY: CS_Work lab0 lab1 lab2 lab3 lab4 lab5 lab6 lab7 lab8 all clean clean_all
all: CS_Work lab0 lab1 lab2 lab3 lab4 lab5 lab6 lab7 lab8 clean
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
lab3: $(TARGET3)
$(TARGET3): $(OBJS3)
	$(CC) $(CFLAGS) -o $@ $(OBJS3) $(LIBS)
lab4: $(TARGET4)
$(TARGET4): $(OBJS4)
	$(CC) $(CFLAGS) -o $@ $(OBJS4) $(LIBS)
lab5: $(TARGET5)
$(TARGET5): $(OBJS5)
	$(CC) $(CFLAGS) -o $@ $(OBJS5) $(LIBS)
lab6: $(TARGET6)
$(TARGET6): $(OBJS6)
	$(CC) $(CFLAGS) -o $@ $(OBJS6) $(LIBS)
lab7: $(TARGET7)
$(TARGET7): $(OBJS7)
	$(CC) $(CFLAGS) -o $@ $(OBJS7) $(LIBS)
lab8: $(TARGET8)
$(TARGET8): $(OBJS8)
	$(CC) $(CFLAGS) -o $@ $(OBJS8) $(LIBS)
clean:
	find ../ -name "*.o" -type f -delete
clean_all: clean
	find build/ -name "*.exe" -type f -delete
