SOURCES=addressbook.c addressbook_list.c commands.c helpers.c
HEADERS=addressbook.h addressbook_list.h commands.h helpers.h
PROGRAM=addressbook
FLAGS=-ansi -pedantic -Wall -g

all:
	gcc $(FLAGS) -o $(PROGRAM) $(SOURCES)

clean:
	rm $(PROGRAM)
    
archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) Makefile
