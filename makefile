
Sand: sand.c
	gcc sand.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o sand

clean:
	rm ./sand