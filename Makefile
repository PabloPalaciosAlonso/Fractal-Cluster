all:
	$(MAKE) -C src/ all
	mv src/fc .
clean:
	rm -f bin/fc
	$(MAKE) -C src/ clean
redo: clean all
