CXX = g++
ifeq ($(OS),Windows_NT)
  TARGET = aes.exe
else
  TARGET = aes
endif
CXXFLAGS = -O3 -maes -mpclmul
SRCS = main.cpp aes.cpp
OBJS := $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
clean:
	rm -f $(TARGET) $(OBJS)

# Header Dependencies
main.o: aes.h option.h
aes.o: aes.h
