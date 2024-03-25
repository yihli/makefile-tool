(CXX)=g++
(CXXFLAGS)=-Wall

all: find_includes

find_includes: find_includes.o create_makefile.o file_searcher.o
	$(CXX) $^ -o ../public/$@

clean:
	rm -f *.o find_includes