GTEST_DIR=/usr/local
LDFLAGS=-isystem ${GTEST_DIR}/include -I${GTEST_DIR} ${GTEST_DIR}/lib/libgtest.a ${GTEST_DIR}/lib/libgtest_main.a
CC_FLAGS=-std=c++11
CC=g++

all: histogram_test

histogram_test: histogram_test.o
    ${CC} ${LDFLAGS} histogram_test.o -o histogram_test

histogram_test.o: histogram_test.cc
    ${CC} ${CC_FLAGS} -c histogram_test.cc

test: histogram_test
	./histogram_test

clean:
	rm *.o histogram_test radix_sort
