# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra

# Source and header files
SRC = main.cpp
HDR = expression_evaluator.h
EXEC = main

# LaTeX report
REPORT = report.tex
PDF = $(REPORT:.tex=.pdf)

# Default target
all: $(EXEC)

# Compile the C++ program
$(EXEC): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)

# Run the program
run: $(EXEC)
	./$(EXEC)

# Generate the LaTeX report
report: $(PDF)

$(PDF): $(REPORT)
	xelatex $<
	xelatex $<  # Run twice for cross-references

# Clean up generated files
clean:
	rm -f $(EXEC) *.aux *.log *.out $(PDF)

# Phony targets
.PHONY: all run report clean
