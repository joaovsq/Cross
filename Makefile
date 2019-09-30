
container=54d1599a0461

all: osx linux

prepare:
	mkdir -p /tmp/CrossGameEngine-build

osx: prepare
	docker run -it --rm -v $(shell pwd):/workdir -v /tmp/CrossGameEngine-build:/tmp/CrossGameEngine-build -e CROSS_TRIPLE=osx   $(container) ./.crosscompile.sh

linux: prepare
	docker run -it --rm -v $(shell pwd):/workdir -v /tmp/CrossGameEngine-build:/tmp/CrossGameEngine-build -e CROSS_TRIPLE=linux $(container) ./.crosscompile.sh

clean:
	rm -rf /tmp/CrossGameEngine-build
