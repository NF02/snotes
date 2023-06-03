# See LICENSE for license details
# snotes version
VERSION = 0.1

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# flags
#CPPFLAGS = -DVERSION=\"${VERSION}\"
#CFLAGS   = -g -std=c99 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS}
LDFLAGS = $(shell pkg-config --libs libgit2)
CFLAGS   = -std=c11 $(shell pkg-config --cflags libgit2) #${CPPFLAGS}

# compiler and linker
CC = cc
