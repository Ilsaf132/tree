PATH_CPP = .\Cpp_files
PATH_HEADER = .\Headers\
HEADERS_NAME = TreeLibrary.h Tree.h Akinator.h Definitions.h GraphDump.h SubFunctions.h ConstantsAndErrors.h
HEADERS = $(HEADERS_NAME:%.h=$(PATH_HEADER)%.h)

flags = -IHeaders -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

tree: tree.exe
	@.\tree.exe

tree.exe:TreeMain.o Akinator.o Definitions.o GraphDump.o SubFunctions.o Tree.o
	@g++ TreeMain.o Akinator.o Definitions.o GraphDump.o SubFunctions.o Tree.o -o tree.exe

TreeMain.o: $(PATH_CPP)\TreeMain.cpp $(HEADERS) 
	@g++ -c $(flags) $(PATH_CPP)\TreeMain.cpp 

Akinator.o: $(PATH_CPP)\Akinator.cpp $(HEADERS) 
	@g++ -c $(flags) $(PATH_CPP)\Akinator.cpp 

Definitions.o: $(PATH_CPP)\Definitions.cpp $(HEADERS) 
	@g++ -c $(flags) $(PATH_CPP)\Definitions.cpp 

GraphDump.o: $(PATH_CPP)\GraphDump.cpp $(HEADERS) 
	@g++ -c $(flags) $(PATH_CPP)\GraphDump.cpp 

SubFunctions.o: $(PATH_CPP)\SubFunctions.cpp $(HEADERS) 
	@g++ -c $(flags) $(PATH_CPP)\SubFunctions.cpp 

Tree.o: $(PATH_CPP)\SubFunctions.cpp $(HEADERS) 
	@g++ -c $(flags) $(PATH_CPP)\Tree.cpp

clean:
	rm -rf *.o *.exe
