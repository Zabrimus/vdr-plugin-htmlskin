# Makefile for webskin skin

MAKEDIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

build:
	npm run build

rundev:	
	npm run serve

preparedev:
	npm install
	
install:
	if ! test -d $(DESTDIR)/skin/; then \
		mkdir -p $(DESTDIR)/skin/; \
	fi
	cp -r dist/* $(DESTDIR)/skin
	chmod -R a+rX $(DESTDIR)
ifdef VDR_USER
	if test -n $(VDR_USER); then \
		chown -R $(VDR_USER) $(DESTDIR); \
	fi
endif	
	
	