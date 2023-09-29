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
	rm -rf build out/*

OSM=$(shell uname -sm)
ifeq ($(OSM),Darwin arm64) # Mac OS X - arm
    M1=-m1
endif
docker-build-sgdk:	pull
	cd ${SGDK_FOLDER} && docker build . -f Dockerfile${M1} -t sgdk:${SGDK_VERSION}${M1}

docker-build:	docker-build-sgdk
	docker run -it --rm -v "${PWD}":/src -w /src sgdk:${SGDK_VERSION}${M1}

docker-shell:
	docker run -it --rm -v "${PWD}":/src -w /src --entrypoint=/bin/bash sgdk:${SGDK_VERSION}${M1}
