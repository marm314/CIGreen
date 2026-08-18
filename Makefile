# Makefile for rho_ops
#
#CPP = c++ -DHAVE_LIBXC /usr/lib/x86_64-linux-gnu/libxc.so
CPP = c++
CPPFLAGS = -Wall -Wl,--allow-multiple-definition -O3 -fopenmp -llapack -lblas -lstdc++ 
Cln = /bin/rm -rf
NAME=CIGreen
###########################################
###########################################
SCR= main.cpp Input_commands.cpp String_ops.cpp gitver.cpp io.cpp
OBJECTS= main.o Input_commands.o String_ops.o gitver.o gitver.o io.o
all:
	./gitversion.sh
	make CIGreen
	make fcidump_sw
	make fcidump_u2d
%.o: %.cpp   
	$(CPP) $(CPPFLAGS) -c $*.cpp 
CIGreen: $(OBJECTS) $(SCR) Makefile 
	$(CPP) $(CPPFLAGS) $(OBJECTS) -o CIGreen.x
fcidump_sw: fcidump_sw.cpp Makefile 
	$(CPP) fcidump_sw.cpp -o fcidump_sw
fcidump_u2d: fcidump_u2d.cpp Makefile 
	$(CPP) fcidump_u2d.cpp -o fcidump_u2d
clean:
	$(Cln) *.o
	$(Cln) *CIGreen.x
	$(Cln) *fcidump_sw
	$(Cln) *fcidump_u2d
	$(Cln) *~
	$(Cln) gitver.cpp gitver.o gitver.h
	$(Cln) $(NAME).tar.gz 
tar:
	mkdir $(NAME)
	cp *.cpp *.h Makefile ./$(NAME)
	tar -pczf $(NAME).tar.gz ./$(NAME)
	rm -r ./$(NAME)
	cp ./*.tar.gz ../

