all: BackgroundChanger

BackgroundChanger: BackgroundChanger.c
	gcc BackgroundChanger.c -o BackgroundChanger -laquaterm -lobjc

clean:
	rm -f BackgroundChanger
