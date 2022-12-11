all: WorldOfIUT

exits.o: exits.h
game.o: game.h mobile.h exits.h location.h types.h
location.o: location.h stack.h exits.h game.h types.h
stack.o: stack.h location.h types.h
object.o: object.h types.h
cmd.o: cmd.h game.h exits.h mobile.h location.h types.h
mobile.o: mobile.h exits.h location.h types.h
WorldOfIUT.o: cmd.h exits.h mobile.h game.h types.h
WorldOfIUT: WorldOfIUT.o cmd.o mobile.o game.o exits.o location.o stack.o object.o
clean:
	/bin/rm *.o WorldOfIUT
