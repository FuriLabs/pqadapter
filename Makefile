CC = gcc

CFLAGS = $(shell pkg-config --cflags gio-2.0 libgbinder) -Iinclude
LDFLAGS = $(shell pkg-config --libs gio-2.0 libgbinder alsa libandroid-properties)

SOURCES_GSD_ADAPTER = src/gsd-adapter.c src/alsa.c
SOURCES_PQCLI = src/pqcli.c
SOURCES_LIBPQ = src/pq.c
SOURCES_PQDBUS = src/pqdbus.c
HEADERS = include/pq.h

TARGET_GSD_ADAPTER = gsd-adapter
TARGET_PQCLI = pqcli
TARGET_LIBPQ = libpq.so
TARGET_PQDBUS = pqdbus

PREFIX ?= /usr
TRIPLET ?= $(shell $(CC) -dumpmachine)

.PHONY: all clean install compile-schemas

all: $(TARGET_LIBPQ) $(TARGET_GSD_ADAPTER) $(TARGET_PQCLI) $(TARGET_PQDBUS)

$(TARGET_LIBPQ): $(SOURCES_LIBPQ)
	$(CC) $(CFLAGS) -fPIC -shared $^ $(LDFLAGS) -o $@

$(TARGET_GSD_ADAPTER): $(SOURCES_GSD_ADAPTER) $(TARGET_LIBPQ)
	$(CC) $(CFLAGS) $(SOURCES_GSD_ADAPTER) -L. -lpq $(LDFLAGS) -o $@

$(TARGET_PQCLI): $(SOURCES_PQCLI) $(TARGET_LIBPQ)
	$(CC) $(CFLAGS) $< -L. -lpq $(LDFLAGS) -o $@

$(TARGET_PQDBUS): $(SOURCES_PQDBUS) $(TARGET_LIBPQ)
	$(CC) $(CFLAGS) $< -L. -lpq $(LDFLAGS) -o $@

install: all
	install -d $(DESTDIR)$(PREFIX)/bin/
	install -m 0755 $(TARGET_PQCLI) $(DESTDIR)$(PREFIX)/bin/
	install -d $(DESTDIR)$(PREFIX)/libexec/
	install -m 0755 $(TARGET_GSD_ADAPTER) $(DESTDIR)$(PREFIX)/libexec/
	install -m 0755 $(TARGET_PQDBUS) $(DESTDIR)$(PREFIX)/libexec/
	install -d $(DESTDIR)$(PREFIX)/lib/systemd/user/
	install -m 0644 data/gsd-adapter.service $(DESTDIR)$(PREFIX)/lib/systemd/user/gsd-adapter.service
	install -m 0644 data/pqdbus.service $(DESTDIR)$(PREFIX)/lib/systemd/user/pqdbus.service
	install -d $(DESTDIR)$(PREFIX)/lib/$(TRIPLET)/
	install -m 0644 $(TARGET_LIBPQ) $(DESTDIR)$(PREFIX)/lib/$(TRIPLET)/
	install -d $(DESTDIR)$(PREFIX)/include/
	install -m 0644 $(HEADERS) $(DESTDIR)$(PREFIX)/include/
	install -d $(DESTDIR)$(PREFIX)/share/glib-2.0/schemas/
	install -m 0644 data/io.furios.pq.gschema.xml $(DESTDIR)$(PREFIX)/share/glib-2.0/schemas/io.furios.pq.gschema.xml

compile-schemas:
	glib-compile-schemas $(DESTDIR)$(PREFIX)/share/glib-2.0/schemas/

clean:
	rm -f $(TARGET_GSD_ADAPTER) $(TARGET_PQCLI) $(TARGET_LIBPQ) $(TARGET_PQDBUS)
