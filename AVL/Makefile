# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -O2
LATEX = xelatex

# Source and header files
SRC = test.cpp
HDR = BST.h
# Output executable
EXEC = test

# LaTeX report
REPORT = report.tex

# Default target
all: $(EXEC)

# Compile the C++ program
$(EXEC): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)

# Run the program and output results to a file
run: $(EXEC)
	./$(EXEC)

# Generate the LaTeX report
report:
	$(LATEX) $(REPORT)
	$(LATEX) $(REPORT)  # Run twice for cross-references

# Clean up generated files
clean:
	rm -f $(EXEC) *.aux *.log *.out *.pdf output.txt

# Phony targets
.PHONY: all run report clean
