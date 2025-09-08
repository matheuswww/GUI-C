OBJDIR := obj
BINDIR := dos

flags := -fno-stack-protector -O0 -Wall -std=gnu23 -m16 -fno-pie -fno-pic
flags += -ffreestanding -I include -nostdlib
ldflags := -m elf_i386 --nmagic --script=gui.ld
objects := $(OBJDIR)/main.o $(OBJDIR)/shapes.o $(OBJDIR)/bmp.o $(OBJDIR)/omnistd.o
xobjects := $(OBJDIR)/xgfx.o
NASMENV := -i include/asm/
export NASMENV

.PHONY: clean

all: $(BINDIR)/gui.com

$(BINDIR)/gui.com: $(objects) $(xobjects)
	ld $(ldflags) $^ -o $@

$(OBJDIR)/omnistd.o: omnistd.c
	cc $(flags) -c $^ -o $@

$(OBJDIR)/bmp.o: bmp.c
	cc $(flags) -c $^ -o $@

$(OBJDIR)/main.o: main.c
	cc $(flags) -c $^ -o $@

$(OBJDIR)/xgfx.o: xgfx.asm
	nasm -f elf $^ -o $@

$(OBJDIR)/shapes.o: shapes.c
	cc $(flags) -c $^ -o $@

clean:
	rm -rf $(OBJDIR)/* $(BINDIR)/gui.com