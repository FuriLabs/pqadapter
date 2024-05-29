CC=gcc

CFLAGS=$(shell pkg-config --cflags glib-2.0 gio-2.0 libgbinder alsa libandroid-properties)
LDFLAGS=$(shell pkg-config --libs glib-2.0 gio-2.0 libgbinder alsa libandroid-properties)

GSD_ADAPTER_SRCS=gsd-adapter.c pq.c alsa.c
PQCLI_SRCS=pqcli.c pq.c
LIBPQ_SRCS=pq.c
PQDBUS_SRCS=pqdbus.c pq.c

GSD_ADAPTER_BIN=gsd-adapter
PQCLI_BIN=pqcli
LIBPQ=libpq.so
PQDBUS_BIN=pqdbus

PREFIX?=/usr

.PHONY: all clean install compile-schemas

all: $(GSD_ADAPTER_BIN) $(PQCLI_BIN) $(LIBPQ) $(PQDBUS_BIN)

$(GSD_ADAPTER_BIN): $(GSD_ADAPTER_SRCS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(PQCLI_BIN): $(PQCLI_SRCS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(LIBPQ): $(LIBPQ_SRCS)
	$(CC) $(CFLAGS) -shared $^ $(LDFLAGS) -o $@

$(PQDBUS_BIN): $(PQDBUS_SRCS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

install: all
	install -D -m 0755 $(PQCLI_BIN) debian/tmp$(PREFIX)/bin/$(PQCLI_BIN)
	install -D -m 0755 $(GSD_ADAPTER_BIN) debian/tmp$(PREFIX)/libexec/$(GSD_ADAPTER_BIN)
	install -D -m 0644 gsd-adapter.service debian/tmp$(PREFIX)/lib/systemd/user/gsd-adapter.service
	install -D -m 0644 $(LIBPQ) debian/libpq$(PREFIX)/lib/$(shell dpkg-architecture -qDEB_HOST_MULTIARCH)/$(LIBPQ)
	install -D -m 0644 pq.h debian/tmp$(PREFIX)/include/pq.h
	install -D -m 0755 $(PQDBUS_BIN) debian/tmp$(PREFIX)/libexec/$(PQDBUS_BIN)
	install -D -m 0644 pqdbus.service debian/tmp$(PREFIX)/lib/systemd/user/pqdbus.service
	install -D -m 0644 io.furios.pq.gschema.xml debian/tmp$(PREFIX)/share/glib-2.0/schemas/io.furios.pq.gschema.xml
	install -D -m 0644 50-org.freedesktop.systemd1.manage-units.rules debian/tmp$(PREFIX)/share/polkit-1/rules.d/50-org.freedesktop.systemd1.manage-units.rules

compile-schemas:
	glib-compile-schemas debian/tmp$(PREFIX)/share/glib-2.0/schemas/

clean:
	rm -f $(GSD_ADAPTER_BIN) $(PQCLI_BIN) $(LIBPQ) $(PQDBUS_BIN)
