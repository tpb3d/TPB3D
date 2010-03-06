CC=g++
CFLAGS=-O3
LFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
AR=ar
SRCS=highrisedev.cpp physics.cpp camera.cpp image.cpp animation.cpp \
     citizens.cpp person.cpp interface.cpp tiler.cpp \
     AI/citizensAgent.cpp AI/pathAgent.cpp AI/floorAgent.cpp \
     Graphics\ErrorImage.cpp Graphics\image.cpp \
     Tower/tower.cpp Tower/apartment.cpp \
     Tower/floorbase.cpp Tower/office.cpp Tower/level.cpp Tower/lobby.cpp Tower/elevator.cpp \
     Tower/elevatorBase.cpp Tower/elevatorMachine.cpp Tower/elevatorPit.cpp Tower/elevatorShaft.cpp \
     Window/Button.cpp Window/Element.cpp Windows/TextBox.cpp Window/Window.cpp \
     highRiseException.cpp routes.cpp routeVisitor.cpp background.cpp
OBJS=highrisedev.o physics.o camera.o image.o animation.o \
     citizens.o person.o interface.o tiler.o \
     AI/citizensAgent.o AI/pathAgent.o AI/floorAgent.o \
     Graphics\ErrorImage.o Graphics\image.o \
     Tower/tower.o Tower/apartment.o \
     Tower/floorbase.o Tower/office.o Tower/level.o Tower/lobby.o Tower/elevator.o \
     Tower/elevatorBase.o Tower/elevatorMachine.o Tower/elevatorPit.o Tower/elevatorShaft.o \
     Window/Button.o Window/Element.o Windows/TextBox.o Window/Window.o \
     highRiseException.o routes.o routeVisitor.o background.o

all : highrisedev

highrisedev : $(OBJS) $(SRCS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $@

.cpp.o : $(SRCS)
	$(CC) -c $(CFLAGS) $*.cpp

clean : 
	rm -rf *.o *.a *.exe stdout.txt stderr.txt
    
