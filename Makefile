.PHONY : clean

TARGET := strftime
CC := 
CFLAGS := 
SRC_FILES := strftime.c

$(TARGET) : $(SRC_FILES)
	$(CC)gcc -o $@ $^ $(CFLAGS)
	$(CC)strip $@
clean:
	rm -rf $(TARGET) *.d *.o
