.PHONY: all
all:
	cd source && qmake
	make -C source
