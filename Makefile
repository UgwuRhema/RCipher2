CFLAGS := -g -Wall -Wextra -march=native
SRC := ./main.cpp
OUT := ./rcipher2

all: $(SRC)
	c++ $(CFLAGS) $(SRC) -o $(OUT)

run:
	$(OUT)

clean:
	rm -rf $(OUT)

.PHONY: all clean run
