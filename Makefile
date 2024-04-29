default: build

install-deps:
	conan install . --output-folder=build --build=missing -s compiler.cppstd=20 -s build_type=Release

build:
	cmake -S . -B build \
		-DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
		-DCMAKE_BUILD_TYPE=Release \
		-DBUILD_TESTS=1
	make -C build

tests: build
	ctest --test-dir ./build/tests --output-on-failure

lint:
	cppcheck compile_time_regexp.h --enable=warning,style,performance,portability --inline-suppr --language=c++

clean:
	rm -rf build

.PHONY: build lint clean install-deps
