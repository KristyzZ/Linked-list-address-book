.PHONY: all clean run src lib clean-src clean-lib

all: lib src

lib:
	$(MAKE) -C lib

src:
	$(MAKE) -C src


run: all
	./address_book

clean: clean-src clean-lib
	rm -f address_book

clean-src:
	$(MAKE) -C src clean

clean-lib:
	$(MAKE) -C lib clean
