GCC=g++
OPTS=-Wall
DBG_OPTS=-g
LD_OPTS=-lpanel -lncursesw
SOURCE=src/board.cpp \
			 src/debug.cpp \
       src/console.cpp \
			 src/game.cpp \
			 src/main.cpp
APP=mine

all:
	${GCC} ${SOURCE} ${OPTS} ${LD_OPTS} -o ${APP}

debug:
	${GCC} ${SOURCE} ${DBG_OPTS} ${OPTS} ${LD_OPTS} -o ${APP}

clean:
	rm -f ${APP}
