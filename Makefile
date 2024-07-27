CC = gcc

CFLAGS = $(shell pkg-config --cflags glib-2.0 gio-2.0 libgbinder alsa libandroid-properties)
LDFLAGS = $(shell pkg-config --libs glib-2.0 gio-2.0 libgbinder alsa libandroid-properties)

GSD_ADAPTER_SRC = gsd-adapter.c pq.c alsa.c
PQCLI_SRC = pqcli.c pq.c
LIBPQ_SRC = pq.c
PQDBUS_SRC = pqdbus.c pq.c

GSD_ADAPTER = gsd-adapter
PQCLI = pqcli
LIBPQ = libpq.so
PQDBUS = pqdbus

PREFIX ?= /usr

.PHONY: all clean install compile-schemas

all: $(GSD_ADAPTER) $(PQCLI) $(LIBPQ) $(PQDBUS)

$(GSD_ADAPTER): $(GSD_ADAPTER_SRC)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(PQCLI): $(PQCLI_SRC)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(LIBPQ): $(LIBPQ_SRC)
	$(CC) $(CFLAGS) -shared $^ $(LDFLAGS) -o $@

$(PQDBUS): $(PQDBUS_SRC)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

install: all
	install -D -m 0755 $(PQCLI) debian/tmp$(PREFIX)/bin/$(PQCLI)
	install -D -m 0755 $(GSD_ADAPTER) debian/tmp$(PREFIX)/libexec/$(GSD_ADAPTER)
	install -D -m 0644 gsd-adapter.service debian/tmp$(PREFIX)/lib/systemd/user/gsd-adapter.service
	install -D -m 0644 $(LIBPQ) debian/libpq$(PREFIX)/lib/$(shell dpkg-architecture -qDEB_HOST_MULTIARCH)/$(LIBPQ)
	install -D -m 0644 pq.h debian/tmp$(PREFIX)/include/pq.h
	install -D -m 0755 $(PQDBUS) debian/tmp$(PREFIX)/libexec/$(PQDBUS)
	install -D -m 0644 pqdbus.service debian/tmp$(PREFIX)/lib/systemd/user/pqdbus.service
	install -D -m 0644 io.furios.pq.gschema.xml debian/tmp$(PREFIX)/share/glib-2.0/schemas/io.furios.pq.gschema.xml
	install -D -m 0644 50-org.freedesktop.systemd1.manage-units.rules debian/tmp$(PREFIX)/share/polkit-1/rules.d/50-org.freedesktop.systemd1.manage-units.rules

compile-schemas:
	glib-compile-schemas debian/tmp$(PREFIX)/share/glib-2.0/schemas/

clean:
	rm -f $(GSD_ADAPTER) $(PQCLI) $(LIBPQ) $(PQDBUS)
