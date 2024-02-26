SDIR := src
TDIR := test
BDIR := bench
IDIR := include
ODIR := obj

CXX := g++
CXXFLAGS := -std=c++17 -I $(IDIR)

SRCS := $(shell find $(SDIR) -name '*.cpp')
OBJS := $(SRCS:$(SDIR)/%.cpp=$(ODIR)/%.o)

TSRCS := $(shell find $(TDIR) -name '*.cpp'; find $(SDIR) -name '*.cpp' -a \! -name 'main.cpp')
TOBJS := $(TSRCS:$(TDIR)/%.cpp=$(ODIR)/%.o)
TOBJS := $(TOBJS:$(SDIR)/%.cpp=$(ODIR)/%.o)

BSRCS := $(shell find $(BDIR) -name '*.cpp'; find $(SDIR) -name '*.cpp' -a \! -name 'main.cpp')
BOBJS := $(BSRCS:$(BDIR)/%.cpp=$(ODIR)/%.o)
BOBJS := $(BOBJS:$(SDIR)/%.cpp=$(ODIR)/%.o)

HDRS := $(shell find $(IDIR) -name *.hpp)

.PHONY: clean

ray-tracer: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o ray-tracer

testing: $(TOBJS)
	$(CXX) $(CXXFLAGS) $^ -o testing

benching: $(BOBJS)
	$(CXX) $(CXXFLAGS) $^ -o benching

$(ODIR)/%.o: $(SDIR)/%.cpp $(HDRS) | $(ODIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(ODIR)/%.o: $(TDIR)/%.cpp $(HDRS) | $(ODIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(ODIR)/%.o: $(BDIR)/%.cpp $(HDRS) | $(ODIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@

clean:
	rm -rf $(ODIR) a.out testing ray-tracer *.ppm valgrind-out.* vgcore.*
