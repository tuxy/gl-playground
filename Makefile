all: main

main:
	cmake -S . -B build
	make -C build

clean:
	rm -rf build/
