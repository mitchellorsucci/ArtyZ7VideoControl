CC=gcc
ARCH= arm

SOURCES= resChange.c drmdemo.c
HEADERS= resChange.h
EXECUTABLE= drmdemo

$(EXECUTABLE): $(SOURCES) $(HEADERS)        
	$(CC) -std=gnu99 -g -o $(EXECUTABLE) $(SOURCES)

.PHONY: clean

clean:  
	rm -f *.o *~ $(EXECUTABLE) $(EXECUTABLE1) 
