CFLAGS= -Wall -Werror -Wextra -g
CC=g++
SRC=main.cpp list.cpp database.cpp record.cpp
OBJS=$(SRC:.c=.o)
ODIR=../build/
TARGET=$(ODIR)CS_Work.exe
LIBS=-lm 
.PHONY: all clean clean_all
all: $(TARGET) clean
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	find ../ -name "*.o" -type f -delete
clean_all: clean
	find ../build/ -name "*." -type f -delete
