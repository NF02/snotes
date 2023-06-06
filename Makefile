# Snote - Simple Note
# See LICENSE file for copyright and license details.

include config.mk

SRC = snotes.c file.c gitSync.c timeGet.c
OBJ = ${SRC:.c=.o}

all: options snotes

options:
	@echo snotes build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

snotes: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f snotes ${OBJ} snotes-${VERSION}.tar.gz

dist: clean
	mkdir -p snotes-${VERSION}
	cp -R LICENSE Makefile README.org config.def.h config.mk\
		snote.1 ${SRC} snotes-${VERSION}
	tar -cf snotes-${VERSION}.tar snotes-${VERSION}
	gzip snotes-${VERSION}.tar
	rm -rf snotes-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f snotes ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/snotes
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < snotes.1 > ${DESTDIR}${MANPREFIX}/man1/snotes.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/snotes.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/snotes\
		${DESTDIR}${MANPREFIX}/man1/snote.1

.PHONY: all options clean dist install uninstall
