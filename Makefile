# Makefile for rho_ops
#
CPP = c++
CPPFLAGS = -Wall -Wl,--allow-multiple-definition -O3 -fopenmp
Cln = /bin/rm -rf
NAME=CIGreen
###########################################
###########################################
SCR= main.cpp Input_commands.cpp Mathematical_Functions.cpp String_ops.cpp gitver.cpp io.cpp Gpq.cpp
OBJECTS= main.o Input_commands.o Mathematical_Functions.o String_ops.o gitver.o gitver.o io.o Gpq.o
all:
	./gitversion.sh
	make CIGreen
	make fci_sw
	make fci_u2d
%.o: %.cpp   
	$(CPP) $(CPPFLAGS) -c $*.cpp 
CIGreen: $(OBJECTS) $(SCR) Makefile 
	$(CPP) $(CPPFLAGS) $(OBJECTS) -o CIGreen.x -llapack -lblas -lstdc++
fci_sw: fci_sw.cpp Makefile 
	$(CPP) fci_sw.cpp -o fci_sw
fci_u2d: fci_u2d.cpp Makefile 
	$(CPP) fci_u2d.cpp -o fci_u2d
clean:
	$(Cln) *.o
	$(Cln) *CIGreen.x
	$(Cln) *fci_sw
	$(Cln) *fci_u2d
	$(Cln) *~
	$(Cln) gitver.cpp gitver.o gitver.h
	$(Cln) $(NAME).tar.gz 
tar:
	mkdir $(NAME)
	cp *.cpp *.h Makefile ./$(NAME)
	tar -pczf $(NAME).tar.gz ./$(NAME)
	rm -r ./$(NAME)
	cp ./*.tar.gz ../

