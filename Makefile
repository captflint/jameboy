jameboy: jameboy.o lcd.o
	gcc -o jameboy jameboy.o lcd.o -lSDL2

jameboy.o: jameboy.c lcd.h
	gcc -c jameboy.c

lcd.o: lcd.c lcd.h
	gcc -c lcd.c

clean:
	rm jameboy *.o


