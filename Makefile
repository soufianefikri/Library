SRC=$(wildcart *.c)
OBJ=$(SRC : .c=.o)
exec: $(OBJ)
      gcc $^ -o $@
%.o: %.c header.h
      gcc -c $< -o f $@
#supprimer tous les fichiers objets
clear:
      rm *.o 
