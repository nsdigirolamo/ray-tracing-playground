SDIR := src
TDIR := test
IDIR := include
ODIR := obj

CXX := g++
CXXFLAGS := -std=c++2b -I $(IDIR)

SRCS := $(shell find $(SDIR) -name '*.cpp')
OBJS := $(SRCS:$(SDIR)/%.cpp=$(ODIR)/%.o)

TSRCS := $(shell find $(TDIR) -name '*.cpp')
TOBJS := $(TSRCS:$(TDIR)/%.cpp=$(ODIR)/%.o)

HDRS := $(shell find $(IDIR) -name *.hpp)

.PHONY: clean

nicks-ray-tracer: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o nicks-ray-tracer

$(ODIR)/%.o: $(SDIR)/%.cpp $(HDRS) | $(ODIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

testing: $(TOBJS)
	$(CXX) $(CXXFLAGS) $^ -o testing

$(ODIR)/%.o: $(TDIR)/%.cpp $(HDRS) | $(ODIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@

clean:
	rm -rf $(ODIR) a.out testing nicks-ray-tracer *.ppm
