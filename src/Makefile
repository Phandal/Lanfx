CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = 
BINS = frame_decode frame_encode

frame_decode: frame_decode.c lifx.o
	$(CC) $(CFLAGS) $(LFLAGS) $^ -g -o $@

frame_encode: frame_encode.c lifx.o
	$(CC) $(CFLAGS) $(LFLAGS) $^ -g -o $@

.PHONY: clean
clean:
	-rm -rf $(BINS) *.o

