# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -O2
LATEX = xelatex

# Source files
SRC = main.cpp
# Output executable
EXEC = BST

# LaTeX report
REPORT = report.tex

# Default target
all: $(EXEC)

# Compile the C++ program
$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)

# Run the program and output results
run: $(EXEC)
	./$(EXEC)

# Generate the LaTeX report
report:
	$(LATEX) $(REPORT)

# Clean up generated files
clean:
	rm -f $(EXEC) *.aux *.log *.out *.pdf output.txt

# Phony targets
.PHONY: all run report clean
