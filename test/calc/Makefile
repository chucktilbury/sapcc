# Make the test program

TARGET	=	calc
OBJS	=	calc_parser.o \
			calc_ast.o

SRCS	=	$(OBJS:.o=.c)

SAPCC	=	../../bin/sapcc
VERBO	=	-v0
WARN	=	-Wall -Wextra -Wpedantic
DEBUG	=	-g
LDIRS	=	-L../../bin
IDIRS	=	-I ../../src/util
LIBS	=	-lutil -lgc
CARGS	=	$(WARN) $(IDIRS) $(DEBUG)
LARGS	=	$(DEBUG) -o $(TARGET) $(LDIRS) $(OBJS) $(LIBS)

all: $(TARGET)

%.o:%.c
	gcc $(CARGS) -c -o $@ $^

$(TARGET): $(OBJS)
	gcc $(LARGS)

$(SRCS): calc.g
	$(SAPCC) ./calc.g $(VERBO)

calc_parser.o: calc_parser.c
calc_ast.o: calc_ast.c

clean:
	$(RM) $(TARGET) *.c *.h *.o