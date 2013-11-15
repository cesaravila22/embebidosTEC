APP=sirena
BB=~/ti-sdk-beagleboard-06.00.00.00/targetNFS/home/root/repmp3
SRC=$(APP).c
CC=gcc
CROSS_COMPILE=arm-linux-gnueabihf-
FLAGS+=$(shell pkg-config --cflags --libs gstreamer-0.10)

all: $(APP)

$(APP): $(SRC)
		$(CROSS_COMPILE)$(CC) $(SRC) -o $(BB) $(FLAGS)
		$(CC) $(SRC) -o $(APP) $(FLAGS)

x86: 
		$(CC) $(SRC) -o $(APP) $(FLAGS)

BB-xM: 
		$(CROSS_COMPILE)$(CC) $(SRC) -o $(BB) $(FLAGS)

clean:
		rm $(APP) $(BB)
