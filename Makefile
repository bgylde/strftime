.PHONY : clean \
	 debug \
	 install \
	 uninstall 

TARGET:=strftime
CC:=
CFLAGS:=
SRC_FILES:=strftime.c
DEBUG:=STRF_DEBUG
PREFIX:=/usr/local/bin

all : $(TARGET)

$(TARGET) : $(SRC_FILES)
	$(CC)gcc -o $@ $^ $(CFLAGS)
	$(CC)strip $@

debug : $(SRC_FILES)
	$(CC)gcc -g -o $(TARGET) $^ -D$(DEBUG) $(CFLAGS)

install: $(TARGET)
	chmod +x $(TARGET)
	cp $(TARGET) $(PREFIX)

uninstall: 
	rm -rf $(PREFIX)/$(TARGET)

clean:
	rm -rf $(TARGET) *.d *.o *.dSYM
