CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = 
BINS = frame_decode

frame_decode: frame_decode.c
	$(CC) $(CFLAGS) $(LFLAGS) $^ -g -o $@

.PHONY: clean
clean:
	-rm -rf $(BINS)
