CC=clang -Wall

PROGRAMMES=test_terrain test_robot robot_terrain curiosity curiosity-test test_generation_terrains curiosity-perf curiosity-obs

all: $(PROGRAMMES)

######################################################################
#                       Règles de compilation                        #
######################################################################

%.o: %.c
	$(CC) -c $<

test_terrain.o: test_terrain.c terrain.h

test_robot.o: test_robot.c robot.h

robot_terrain.o: robot_terrain.c terrain.h robot.h

robot.o: robot.c robot.h

terrain.o: terrain.c terrain.h

environnement.o: environnement.c environnement.h robot.h terrain.h observateur.h 

programme.o: programme.c programme.h type_pile.h

generation_terrains.o : generation_terrains.c generation_terrains.h

curiosity-perf.o : curiosity-perf.c interprete.h environnement.h observateur.h programme.h generation_terrains.h \
	robot.h terrain.h type_pile.h  

observateur.o : observateur.c observateur.h robot.h terrain.h


curiosity-obs.o : curiosity-obs.c interprete.h environnement.h programme.h observateur.h  \
   robot.h terrain.h type_pile.h 
    
test_generation_terrains.o : test_generation_terrains.c generation_terrains.h terrain.h

interprete.o: interprete.c interprete.h environnement.h \
	programme.h type_pile.h robot.h terrain.h

interprete%.o: interprete%.c interprete.h environnement.h \
	programme.h type_pile.h robot.h terrain.h

type_pile.o: type_pile.c type_pile.h

curiosity.o: curiosity.c environnement.h observateur.h programme.h \
	interprete.h robot.h terrain.h type_pile.h

curiosity-test.o: curiosity-test.c environnement.h observateur.h programme.h \
	interprete.h robot.h terrain.h type_pile.h

######################################################################
#                       Règles d'édition de liens                    #
######################################################################

test_terrain: test_terrain.o terrain.o
	$(CC) $^ -o $@

test_robot: test_robot.o robot.o
	$(CC) $^ -o $@

robot_terrain: robot_terrain.o terrain.o robot.o
	$(CC) $^ -o $@

curiosity: curiosity.o environnement.o observateur.o programme.o interprete.o \
	robot.o terrain.o type_pile.o
	$(CC) $^ -o $@

curiosity-test: curiosity-test.o environnement.o observateur.o programme.o interprete.o \
	robot.o terrain.o type_pile.o
	$(CC) $^ -o $@
generation_terrains : generation_terrains.o generation_terrains.o

curiosity-perf : curiosity-perf.o interprete.o environnement.o observateur.o programme.o generation_terrains.o \
    robot.o terrain.o type_pile.o

curiosity-obs : curiosity-obs.o interprete.o environnement.o programme.o observateur.o\
    robot.o terrain.o type_pile.o

test_generation_terrains : test_generation_terrains.o generation_terrains.o terrain.o

curiosity-test%: curiosity-test.o environnement.o observateur.o programme.o interprete%.o \
	robot.o terrain.o type_pile.o
	$(CC) $^ -o $@

clean:
	rm -f $(PROGRAMMES) *.o
