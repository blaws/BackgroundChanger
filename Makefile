all: BackgroundChanger

BackgroundChanger: BackgroundChanger.c
	gcc BackgroundChanger.c -o BackgroundChanger -Wall

clean:
	rm -f BackgroundChanger *~
