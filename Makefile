CC=gcc

CFLAGS=$(shell pkg-config --cflags glib-2.0 gio-2.0 libgbinder alsa libandroid-properties)
LDFLAGS=$(shell pkg-config --libs glib-2.0 gio-2.0 libgbinder alsa libandroid-properties)

GSD_ADAPTER_SRCS=gsd-adapter.c pq.c alsa.c
PQCLI_SRCS=pqcli.c pq.c
LIBPQ_SRCS=pq.c

GSD_ADAPTER_BIN=gsd-adapter
PQCLI_BIN=pqcli
LIBPQ=libpq.so

.PHONY: all clean

all: $(GSD_ADAPTER_BIN) $(PQCLI_BIN) $(LIBPQ)

$(GSD_ADAPTER_BIN): $(GSD_ADAPTER_SRCS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(PQCLI_BIN): $(PQCLI_SRCS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(LIBPQ): $(LIBPQ_SRCS)
	$(CC) $(CFLAGS) -shared $^ $(LDFLAGS) -o $@

clean:
	rm -f $(GSD_ADAPTER_BIN) $(PQCLI_BIN) $(LIBPQ)
