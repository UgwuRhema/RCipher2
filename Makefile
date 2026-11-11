CFLAGS := -g -Wall -Wextra -O2 -march=native
SRC := ./main.cpp
OUT := ./rcipher2

all: $(SRC)
	cc $(CFLAGS) $(SRC) -o $(OUT)

run:
	$(OUT)

clean:
	rm -rf $(OUT)

.PHONY: all clean run
