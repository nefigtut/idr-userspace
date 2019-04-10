
CFLAGS += -I. -I../../include -g -O1 -Wall -D_LGPL_SOURCE
LDFLAGS += -lpthread -lurcu
TARGETS = main
OFILES = main.o idr.o linux.o find_next_bit.o

targets: $(TARGETS)

main:	$(OFILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OFILES) -o main

clean:
	$(RM) -v $(TARGETS) *.o idr.c

$(OFILES): */*.h ../../../include/linux/idr.h ../../include/linux/*.h

idr.c: ../../../lib/idr.c
	sed -e 's/^static //' -e 's/__always_inline //' -e 's/inline //' < $< > $@
