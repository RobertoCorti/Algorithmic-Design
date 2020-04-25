CXX = gcc 
FLAGS = -O3 -Wall -Wextra
EXE = test_insert
SRC = main.c src/binheap.c src/total_orders.c
INCLUDE = include


$(EXE): $(SRC)
	$(CXX) $^ -o $@ -I $(INCLUDE) $(FLAGS)

clean:
	rm -fr $(EXE)

.PHONY: clean all
