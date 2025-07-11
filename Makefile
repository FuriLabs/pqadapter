CC = gcc
CFLAGS = $(shell pkg-config --cflags glib-2.0 gio-2.0 libgbinder alsa libandroid-properties)
LDFLAGS = $(shell pkg-config --libs glib-2.0 gio-2.0 libgbinder alsa libandroid-properties)

SOURCES_GSD_ADAPTER = gsd-adapter.c pq.c alsa.c
SOURCES_PQCLI = pqcli.c pq.c
SOURCES_LIBPQ = pq.c
SOURCES_PQDBUS = pqdbus.c pq.c

TARGET_GSD_ADAPTER = gsd-adapter
TARGET_PQCLI = pqcli
TARGET_LIBPQ = libpq.so
TARGET_PQDBUS = pqdbus

PREFIX ?= /usr
TRIPLET ?= $(shell $(CC) -dumpmachine)

.PHONY: all clean install compile-schemas

all: $(TARGET_GSD_ADAPTER) $(TARGET_PQCLI) $(TARGET_LIBPQ) $(TARGET_PQDBUS)

$(TARGET_GSD_ADAPTER): $(SOURCES_GSD_ADAPTER)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(TARGET_PQCLI): $(SOURCES_PQCLI)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(TARGET_LIBPQ): $(SOURCES_LIBPQ)
	$(CC) $(CFLAGS) -shared $^ $(LDFLAGS) -o $@

$(TARGET_PQDBUS): $(SOURCES_PQDBUS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

install: all
	install -d $(DESTDIR)$(PREFIX)/bin/
	install -m 0755 $(TARGET_PQCLI) $(DESTDIR)$(PREFIX)/bin/$(PQCLI)

	install -d $(DESTDIR)$(PREFIX)/libexec/
	install -m 0755 $(TARGET_GSD_ADAPTER) $(DESTDIR)$(PREFIX)/libexec/$(GSD_ADAPTER)
	install -m 0755 $(TARGET_PQDBUS) $(DESTDIR)$(PREFIX)/libexec/$(PQDBUS)

	install -d $(DESTDIR)$(PREFIX)/lib/systemd/user/
	install -m 0644 gsd-adapter.service $(DESTDIR)$(PREFIX)/lib/systemd/user/gsd-adapter.service
	install -m 0644 pqdbus.service $(DESTDIR)$(PREFIX)/lib/systemd/user/pqdbus.service

	install -d $(DESTDIR)$(PREFIX)/lib/$(TRIPLET)/
	install -m 0644 $(TARGET_LIBPQ) $(DESTDIR)$(PREFIX)/lib/$(TRIPLET)/$(LIBPQ)

	install -d $(DESTDIR)$(PREFIX)/include/
	install -m 0644 pq.h $(DESTDIR)$(PREFIX)/include/pq.h

	install -d $(DESTDIR)$(PREFIX)/share/glib-2.0/schemas/
	install -m 0644 io.furios.pq.gschema.xml $(DESTDIR)$(PREFIX)/share/glib-2.0/schemas/io.furios.pq.gschema.xml

compile-schemas:
	glib-compile-schemas $(DESTDIR)$(PREFIX)/share/glib-2.0/schemas/

clean:
	rm -f $(TARGET_GSD_ADAPTER) $(TARGET_PQCLI) $(TARGET_LIBPQ) $(TARGET_PQDBUS)
