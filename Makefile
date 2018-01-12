LIBS=-L/usr/X11R6/lib -lglui -lX11 -lm -framework OpenGL -framework GLUT 
OPTS= -Wall -O2 -g
TARGETS= assignment_chitire.o Sphere.o TraceObject.o Wall.o ar3.o
SNOWTARGETS= snowman.o Sphere.o TraceObject.o Wall.o Floor.o ar3.o
TESTTARGS = Sphere.o TraceObject.o Wall.o ar3.o test.o

run: assignment_chitire
	./assignment_chitire

snowman: ${SNOWTARGETS}
	g++ -o snowman ${OPTS} ${LIBS} ${SNOWTARGETS}

assignment_chitire: ${TARGETS}
	g++ -o assignment_chitire ${OPTS} ${LIBS} ${TARGETS}

test: ${TESTTARGS}
	g++ -o test ${OPTS} ${LIBS} ${TESTTARGS}

test.o: ${TESTTARGS}
	g++ -c ${OPTS} test.C

snowman.o: snowman.C Sphere.H Floor.H Wall.H TraceObject.H ar3.h
	g++ -c ${OPTS} snowman.C

assignment_chitire.o: assignment_chitire.C Sphere.H Wall.H TraceObject.H ar3.h
	g++ -c ${OPTS} assignment_chitire.C

Sphere.o: Sphere.C Sphere.H TraceObject.H ar3.h
	g++ -c ${OPTS} Sphere.C

Wall.o: Wall.C Wall.H TraceObject.H ar3.h
	g++ -c ${OPTS} Wall.C


Floor.o: Floor.C Floor.H TraceObject.H ar3.h
	g++ -c ${OPTS} Floor.C


TraceObject.o: TraceObject.C TraceObject.H ar3.h
	g++ -c ${OPTS} TraceObject.C

ar3.o: ar3.h ar3.C
	g++ -c ${OPTS} ar3.C

clean: 
	rm *.o assignment_chitire






