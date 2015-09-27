INC_DIR=/usr/local
GTEST_FLAGS=-isystem ${INC_DIR}/include -I${INC_DIR} ${INC_DIR}/lib/libgtest.a ${INC_DIR}/lib/libgtest_main.a
GMOCK_FLAGS=-isystem ${INC_DIR}/include -I${INC_DIR} ${INC_DIR}/lib/libgmock.a ${INC_DIR}/lib/libgmock_main.a
GFLAGS_FLAGS=-isystem ${INC_DIR}/include -I${INC_DIR} ${INC_DIR}/lib/libgflags.a
GLOG_FLAGS=-isystem ${INC_DIR}/include -I${INC_DIR} ${INC_DIR}/lib/libglog.a
GOOGLE_FLAGS=${GTEST_FLAGS} ${GMOCK_FLAGS} ${GFLAGS_FLAGS} ${GLOG_FLAGS}
CC_FLAGS=-std=c++11
CC=g++

all: histogram_test radix_sort_test

histogram_test: histogram_test.o
	${CC} ${GTEST_FLAGS} histogram_test.o -o histogram_test

histogram_test.o: histogram_test.cc
	${CC} ${CC_FLAGS} -c histogram_test.cc

radix_sort_test: radix_sort_test.o
	${CC} ${GOOGLE_FLAGS} radix_sort_test.o -o radix_sort_test

radix_sort_test.o: radix_sort_test.cc
	${CC} ${CC_FLAGS} -c radix_sort_test.cc

test: histogram_test radix_sort_test
	./histogram_test && ./radix_sort_test

clean:
	rm *.o histogram_test radix_sort_test
