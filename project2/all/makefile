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
ROOT=/fs1/eecg/roman/xujian/Course_Work/ECE1387_CAD_Tools/Assignment2

HDR = graphics.h readTestFile.h placer.h net.h drawSymbol.h cells.h easygl_constants.h umfpack.h
SRC = graphics.cpp readTestFile.cpp placer.cpp net.cpp Main.cpp drawSymbol.cpp cells.cpp
EXE = test
BACKUP_FILENAME=`date "+backup-%Y%m%d-%H%M.zip"`
FLAGS = -g -Wall -D$(PLATFORM) -std=c++0x -I$(ROOT)/SuiteSparse/UMFPACK/Include -I$(ROOT)/SuiteSparse/include -I$(ROOT)/SuiteSparse/SuiteSparse_config/ -I$(ROOT)/SuiteSparse/AMD/Include/ -L$(ROOT)/SuitSparse/lib/ -L$(ROOT)/SuiteSparse/UMFPACK/Lib/ -L$(ROOT)/SuiteSparse/AMD/Lib/ -L$(ROOT)/SuiteSparse/SuiteSparse_config/ 

# Need to tell the linker to link to the X11 libraries.
# WIN32 automatically links to the win32 API libraries (no need for flags)

ifeq ($(PLATFORM),X11)
   GRAPHICS_LIBS = -lX11 -lumfpack -lamd -lsuitesparseconfig  -lrt
endif

#include umfpack.mk

$(EXE): graphics.o readTestFile.o placer.o net.o Main.o drawSymbol.o cells.o
	g++ $(FLAGS) graphics.o readTestFile.o placer.o net.o Main.o drawSymbol.o cells.o $(GRAPHICS_LIBS) -o $(EXE)

graphics.o: graphics.cpp $(HDR)
	g++ -c $(FLAGS) graphics.cpp

readTestFile.o: readTestFile.cpp $(HDR)
	g++ -c $(FLAGS) readTestFile.cpp

placer.o: placer.cpp $(HDR)
	g++ -c $(FLAGS) placer.cpp

net.o: net.cpp $(HDR)
	g++ -c $(FLAGS) net.cpp

Main.o: Main.cpp $(HDR)
	g++ -c $(FLAGS) Main.cpp

drawSymbol.o: drawSymbol.cpp $(HDR)
	g++ -c $(FLAGS) drawSymbol.cpp

cells.o: cells.cpp $(HDR)
	g++ -c $(FLAGS) cells.cpp

backup:
# Back up the source, makefile and Visual Studio project & solution. 
	echo Backing up your files into ${BACKUP_FILENAME}
	zip ${BACKUP_FILENAME} $(SRC) $(HDR) makefile easygl.sln easygl.vcxproj

clean:
	rm $(EXE) *.o
