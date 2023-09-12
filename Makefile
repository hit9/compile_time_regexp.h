default: build

build:
	cmake -S . -B build
	make -C build

tests: build
	./build/tests/tests

lint:
	cppcheck compile_time_regexp.hpp --enable=warning,style,performance,portability --inline-suppr

clean:
	rm -rf build
