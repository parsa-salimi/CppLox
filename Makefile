CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = cpplox
OBJECTS = main.o chunk.o value.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
