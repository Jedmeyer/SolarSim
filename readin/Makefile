OPTS = -Wall -g -std=c++11
LIBS = -lGL -lglut -lm
ARCH := $(shell uname)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 LIBS = -I/usr/common/include -I/usr/include/GL -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++

endif

proto-draw: proto-draw.o circle.o
	g++ $(OPTS) -o proto-draw proto-draw.o circle.o $(LIBS)

proto-draw.o: proto-draw.cpp
	g++ $(OPTS) $(MACOSX_DEFINE) -c proto-draw.cpp

circle.o: circle.cpp circle.h
	g++ -g -Wall -std=c++11 -c circle.cpp

clean:
	rm -f *.o proto-draw
