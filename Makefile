.PHONY: all clean run

all:
	$(MAKE) -C lib
	$(MAKE) -C src

run: all
	$(MAKiE) -C src run

clean:
	$(MAKE) -C src clean
	$(MAKE) -C lib clean
	rm -f address_book
