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

UID=$(shell id -u)
GID=$(shell id -g)
docker-build-sgdk:	pull
	cd ${SGDK_FOLDER} && docker build . -t sgdk:${SGDK_VERSION}

docker-compile:
	docker run -it --rm --user ${UID}:${GID} -v "${PWD}":/workdir -w /workdir sgdk:${SGDK_VERSION} make -f /sgdk/makefile.gen

docker-shell:
	docker run -it --rm --user ${UID}:${GID} -v "${PWD}":/workdir -w /workdir --entrypoint=/bin/bash sgdk:${SGDK_VERSION}
