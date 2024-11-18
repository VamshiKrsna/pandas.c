CC=gcc
CFLAGS=-I./include -g
SRCDIR=src
BUILDDIR=build

all: $(BUILDDIR)/main.exe

$(BUILDDIR)/main.exe: $(BUILDDIR)/main.o $(BUILDDIR)/pandas.o
	$(CC) $(BUILDDIR)/main.o $(BUILDDIR)/pandas.o -o $(BUILDDIR)/main.exe

$(BUILDDIR)/main.o: $(SRCDIR)/main.c
	@if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $(BUILDDIR)/main.o

$(BUILDDIR)/pandas.o: $(SRCDIR)/pandas.c
	@if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	$(CC) $(CFLAGS) -c $(SRCDIR)/pandas.c -o $(BUILDDIR)/pandas.o

clean:
	@if exist $(BUILDDIR) rmdir /s /q $(BUILDDIR)

run: $(BUILDDIR)/main.exe
	$(BUILDDIR)/main.exe