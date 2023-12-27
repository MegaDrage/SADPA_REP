CFLAGS=-Wall -Werror -Wextra -g
CC=g++
SRC=main.cpp generator.cpp
SRC1=lab0/main.cpp generator.cpp lab0/libs.cpp
OBJS=$(SRC:.c=.o)
OBJS1=$(SRC1:.c=.o)
TARGET=generator
TARGET2=lab0/lab0.exe

generate_file: $(TARGET) clear
$(TARGET): $(OBJS)	
	@ $(CC) $(CFLAGS) -o $@ $(OBJS)
	@ ./generator

lab0: $(TARGET2) clear
$(TARGET2): $(OBJS1)
	@ $(CC) $(CFLAGS) -o $@ $(OBJS1)


clear: 
	@ rm -rf *.o
	@ rm -rf generator



