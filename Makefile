.PHONY: all lib src clean clean-lib clean-src install uninsall

all: lib src 

lib:
	$(MAKE) -C lib

src:
	$(MAKE) -C src


clean: clean-lib clean-src

clean-lib:
	$(MAKE) -C lib clean

clean-src:
	$(MAKE) -C src clean


install-lib:
	$(MAKE) -C lib install

uninstall-lib:
	$(MAKE) -C lib uninstall

