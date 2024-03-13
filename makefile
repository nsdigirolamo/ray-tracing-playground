SDIR := src
TDIR := test
IDIR := include
ODIR := obj

CXX := nvcc
CXXFLAGS := -std=c++17 -I $(IDIR)

SRCS := $(shell find $(SDIR) -name '*.cpp' -or -name '*.cu')
OBJS := $(SRCS:$(SDIR)/%=$(ODIR)/%.o)

TSRCS := $(shell find $(TDIR) $(SDIR) \( -name '*.cpp' -and \! -name 'main.cpp' \) -or -name '*.cu')
TOBJS := $(TSRCS:$(TDIR)/%=$(ODIR)/%.o)
TOBJS := $(TSRCS:$(SDIR)/%=$(ODIR)/%.o)

HDRS := $(shell find $(IDIR) -name '*.hpp' -or -name '*.cuh')

.PHONY: clean

tracing: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o ray-tracer

testing: $(TOBJS)
	$(CXX) $(CXXFLAGS) $^ -o testing

$(ODIR)/%.cpp.o: $(SDIR)/%.cpp $(HDRS) | $(ODIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(ODIR)/%.cu.o: $(SDIR)/%.cu $(HDRS) | $(ODIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(ODIR)/%.cpp.o: $(TDIR)/%.cpp $(HDRS) | $(ODIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(ODIR)/%.cu.o: $(TDIR)/%.cu $(HDRS) | $(ODIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@

clean:
	rm -rf $(ODIR) a.out testing ray-tracer *.ppm valgrind-out.* vgcore.*
