# Makefile

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -O2
LATEX = xelatex

# Source files
SRC = List.cpp
# Output executable
EXEC = List

# LaTeX report
REPORT = report.tex

# Default target
all: $(EXEC)

# Compile the C++ program
$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)

# Generate the LaTeX report
report:
	$(LATEX) $(REPORT)

# Clean up generated files
clean:
	rm -f $(EXEC) *.aux *.log *.out *.pdf

# Phony targets
.PHONY: all report clean
