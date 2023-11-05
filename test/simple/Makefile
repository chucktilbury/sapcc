# Make the test program

TARGET	=	simp
SAPCC	=	../../bin/sapcc
VERBO	=	-v0

all: $(TARGET)

$(TARGET): simple_parser.c
	gcc -Wall -Wextra -Wpedantic -g -o $(TARGET) -L../../bin -I ../../src/util simple_parser.c -lutil -lgc

simple_parser.c: simple.g
	$(SAPCC) ./simple.g $(VERBO)

clean:
	$(RM) $(TARGET) *.c *.h