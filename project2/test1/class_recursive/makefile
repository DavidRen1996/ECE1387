# Pick a platform below.  X11 for Linux/Mac/Unix, and WIN32 for windows.
# In either X11 or WIN32, Postscript is also simultaneously available.
# You can also pick NO_GRAPHICS, which will allow your code to compile without
# change on any platform, but no graphics will display (all calls are stubbed
# out).
# 
# Compiling to support X11 requires the X11 development libraries. On Ubuntu, use
# 'sudo apt-get install libx11-dev' to install.
# Please look online for information on how to install X11 on other Linux distributions.

# Please note that a Mac can run the X11 graphics if the X11 library is installed.

PLATFORM = X11
#PLATFORM = WIN32
#PLATFORM = NO_GRAPHICS
ROOT=/u/c/rendongx/ece1387/project2

HDR = create_matrix.h block.h extract.h net.h recurs.h spread.h solver.h umfpack.h
SRC = block.cpp class_recursive.cpp extract.cpp net.cpp recurs.cpp spread.cpp solver.cpp
EXE = test
BACKUP_FILENAME=`date "+backup-%Y%m%d-%H%M.zip"`
FLAGS = -g -Wall -D$(PLATFORM) -std=c++0x -I$(ROOT)/SuiteSparse/UMFPACK/Include -I$(ROOT)/SuiteSparse/include -I$(ROOT)/SuiteSparse/SuiteSparse_config/ -I$(ROOT)/SuiteSparse/AMD/Include/ -L$(ROOT)/SuitSparse/lib/ -L$(ROOT)/SuiteSparse/UMFPACK/Lib/ -L$(ROOT)/SuiteSparse/AMD/Lib/ -L$(ROOT)/SuiteSparse/SuiteSparse_config/ 

# Need to tell the linker to link to the X11 libraries.
# WIN32 automatically links to the win32 API libraries (no need for flags)

ifeq ($(PLATFORM),X11)
   GRAPHICS_LIBS = -lX11 -lumfpack -lamd -lsuitesparseconfig  -lrt
endif

#include umfpack.mk

$(EXE): create_matrix.o block.o class_recursive.o net.o extract.o recurs.o spread.o solver.o
	g++ $(FLAGS) create_matrix.o block.o class_recursive.o net.o extract.o recurs.o spread.o solver.o $(GRAPHICS_LIBS) -o $(EXE)
solver.o: solver.cpp $(HDR)
	g++ -c $(FLAGS) solver.cpp
create_matrix.o: create_matrix.cpp $(HDR)
	g++ -c $(FLAGS) create_matrix.cpp

block.o: block.cpp $(HDR)
	g++ -c $(FLAGS) block.cpp

class_recursive.o: class_recursive.cpp $(HDR)
	g++ -c $(FLAGS) class_recursive.cpp

net.o: net.cpp $(HDR)
	g++ -c $(FLAGS) net.cpp

extract.o: extract.cpp $(HDR)
	g++ -c $(FLAGS) extract.cpp

recurs.o: recurs.cpp $(HDR)
	g++ -c $(FLAGS) recurs.cpp

spread.o: spread.cpp $(HDR)
	g++ -c $(FLAGS) spread.cpp

backup:
# Back up the source, makefile and Visual Studio project & solution. 
	echo Backing up your files into ${BACKUP_FILENAME}
	zip ${BACKUP_FILENAME} $(SRC) $(HDR) makefile easygl.sln easygl.vcxproj

clean:
	rm $(EXE) *.o
