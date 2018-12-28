jameboy: jameboy.o lcd.o memmap.o ppu.o loadTestData.o
	gcc -o jameboy jameboy.o lcd.o memmap.o ppu.o loadTestData.o -lSDL2

jameboy.o: jameboy.c lcd.h memmap.h ppu.h loadTestData.h
	gcc -c jameboy.c

lcd.o: lcd.c lcd.h
	gcc -c lcd.c

memmap.o: memmap.c
	gcc -c memmap.c

ppu.o: ppu.c lcd.h memmap.h
	gcc -c ppu.c

loadTestData.o: loadTestData.c memmap.h
	gcc -c loadTestData.c

clean:
	rm jameboy *.o


