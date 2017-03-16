all:
	echo '#define TESTING' | cat - src/Interface.h > temp && mv temp src/Interface.h;\
	cd test/bin;\
	cmake .;\
	make unittest;\
	./unittest;\
	cd ../..;\
	ex -sc '1d|x' src/Interface.h;\
	platformio run;\

upload:
	platformio run --target upload

clean:
	platformio run --target clean

unittest:
	echo '#define TESTING' | cat - src/Interface.h > temp && mv temp src/Interface.h;\
	cd test/bin;\
	cmake .;\
	make unittest;\
	./unittest;\
	cd ../..;\
