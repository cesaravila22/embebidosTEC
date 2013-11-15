APP=vigilance
SRC=$(APP).cpp
CC=g++
FLAGS+=$(shell pkg-config --cflags --libs gstreamer-0.10 opencv)

all: $(APP)

$(APP): $(SRC)
		$(CC) $(SRC) -o $(APP) $(FLAGS)

clean:
		rm $(APP) $(BB)
