# Make the test program

TARGET	=	calc
SAPCC	=	../../bin/sapcc
VERBO	=	-v0

all: $(TARGET)

$(TARGET): calc_parser.c
	gcc -Wall -Wextra -Wpedantic -g -o $(TARGET) -L../../bin -I ../../src/util calc_parser.c -lutil -lgc

calc_parser.c: calc.g
	$(SAPCC) ./calc.g $(VERBO)

clean:
	$(RM) $(TARGET) *.c *.h