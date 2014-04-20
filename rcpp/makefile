TARGET = rcppTest
SRCS = rcppTest.cpp
CC = g++
CPPFLAGS = -I ./Rcpp/inst/include
LDFLAGS = -lR

All: $(SRCS)
	$(CC) -o $(TARGET) $(CPPFLAGS) $(LDFLAGS) $(SRCS)