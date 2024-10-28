CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2
LDFLAGS = -lssl -lcrypto

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    TARGET = lockedimg
    CROSS_COMPILE =
endif
ifeq ($(UNAME_S),Darwin)
    TARGET = lockedimg
    LDFLAGS += -L/usr/local/opt/openssl/lib
    CFLAGS += -I/usr/local/opt/openssl/include
endif

SRCDIR = source
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(SRCDIR)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CROSS_COMPILE)$(CC) -o $@ $^ $(LDFLAGS)

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
