obj=main.o
INC_DIR=./inc
vpath %.h $(INC_DIR)

target:$(obj)
	@echo "bulid run ...."
	g++ -std=c++11 -pthread $(obj) -o run
main.o:main.cpp semaphore.h
	@echo "bulid main.o  ...."
	g++ -I./inc -c main.cpp
clean:
	rm -rf run *.o
