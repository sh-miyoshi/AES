CXX = g++
TARGET = aes.exe
CXXFLAGS = -O2 -maes -mpclmul
SRCS = main.cpp aes.cpp
OBJS := $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
clean:
	rm -f $(TARGET) $(OBJS)

#�w�b�_�t�@�C���̈ˑ��֌W
main.o: aes.h option.h
aes.o: aes.h
