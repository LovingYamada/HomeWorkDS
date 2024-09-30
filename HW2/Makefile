CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++11

SRCS = Chicken.cpp

TARGET = Chicken

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
