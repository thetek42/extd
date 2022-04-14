target := extd

cc     := gcc
cflags := -Wall -Wextra -Werror
lib    :=

bin    := bin
obj    := obj
src    := src



### DO NOT EDIT BELOW ###

sources := $(shell find $(src) -type f -name *.c)
objects := $(patsubst $(src)/%, $(obj)/%, $(sources:.c=.o))


all: mkdir $(target)

clean:
	@rm -rf $(bin) $(obj)

remake: clean all

.PHONY: all clean remake


mkdir:
	@mkdir -p $(bin) $(obj)

$(target): $(objects)
	$(cc) $(cflags) $(lib) $^ -o $(bin)/$(target)

$(obj)/%.o: $(src)/%.c
	@mkdir -p $(dir $@)
	$(cc) -c $(cflags) $(lib) -o $@ $<

