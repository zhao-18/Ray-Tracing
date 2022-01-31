CC=gcc
CPPFLAGS=-Wall -Werror -I.

_DEPS=ray screen vector

DEPS_H=$(addsuffix .h,$(_DEPS))

_DEPS_O=$(addsuffix .o,$(_DEPS))
OBJ=$(addprefix obj/,$(_DEPS_O))

a.exe : $(OBJ) obj/main.o
	$(CC) -o $@ $^ $(CPPFLAGS) -lm

obj/%.o : %.c $(DEPS_H)
	$(CC) -c $< -o $@ $(CPPFLAGS)
