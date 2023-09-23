SGDK_VERSION=1.90
SGDK_FOLDER=depends/sgdk

pull:
	git submodule update --init --remote --recursive
	cd ${SGDK_FOLDER} && git checkout tags/v${SGDK_VERSION}

.PHONY: build
build:	pull
	mkdir -p build && \
	cd build && \
	cmake .. && \
	make

clean:
	rm -rf build