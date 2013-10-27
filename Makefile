CC=gcc
CFLAGS=-std=c99 -Wall -Werror -O2 -ggdb -pedantic
CSRC=$(wildcard *.c)
BUILDDIR=build
INCDIR=.
INCDIRS=$(addprefix -I,$(INCDIR))
OBJ=$(CSRC:%.c=%.o)
TGT=libthorax.so

$(TGT): $(OBJ)
	@echo LD $@
	@$(CC) -shared -o $@ $(OBJ) $(LDFLAGS)

%.o: %.c $(BUILDIR)
	@echo C $(basename $(notdir $@))
	@$(CC) $(CFLAGS) $(INCDIRS) -c $< -o $@

clean:
	rm *.o 2>/dev/null
	rm $(TGT) 2>/dev/null
