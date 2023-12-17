SDIR := src
TDIR := test
IDIR := include
ODIR := obj

CXX := g++
CXXFLAGS := -std=c++23 -I $(IDIR)

TSRCS := $(shell find $(TDIR) -name *.cpp)
TOBJS := $(TSRCS:$(TDIR)/%.cpp=$(ODIR)/%.o)

HDRS := $(shell find $(IDIR) -name *.hpp)

.PHONY: clean

testing: $(TOBJS)
	$(CXX) $(CXXFLAGS) $^ -o testing

$(ODIR)/%.o: $(TDIR)/%.cpp $(HDRS) | $(ODIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@
	mkdir -p $@/vector
	mkdir -p $@/matrix

clean:
	rm -r $(ODIR) testing
