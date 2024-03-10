SDIR := src
TDIR := test
IDIR := include
ODIR := obj

CXX := nvcc
CXXFLAGS := -std=c++17 -I $(IDIR)

SRCS := $(shell \
			find $(SDIR) -name '*.cpp'; \
			find $(SDIR) -name '*.cu'; \
		)
OBJS := $(SRCS:$(SDIR)/%.cpp=$(ODIR)/%.o)
OBJS := $(SRCS:$(SDIR)/%.cu=$(ODIR)/%.o)

TSRCS := $(shell \
			find $(TDIR) -name '*.cpp'; \
			find $(TDIR) -name '*.cu'; \
			find $(SDIR) -name '*.cpp' -a \! -name 'main.cpp'; \
			find $(SDIR) -name '*.cu'; \
		)
TOBJS := $(TSRCS:$(TDIR)/%.cpp=$(ODIR)/%.o)
TOBJS := $(TSRCS:$(TDIR)/%.cu=$(ODIR)/%.o)
TOBJS := $(TOBJS:$(SDIR)/%.cpp=$(ODIR)/%.o)
TOBJS := $(TOBJS:$(SDIR)/%.cu=$(ODIR)/%.o)

HDRS := $(shell find $(IDIR) -name *.hpp)

.PHONY: clean

ray-tracer: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o ray-tracer

$(ODIR)/%.o: $(SDIR)/%.cpp $(HDRS) | $(ODIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(ODIR)/%.o: $(SDIR)/%.cu $(HDRS) | $(ODIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

testing: $(TOBJS)
	$(CXX) $(CXXFLAGS) $^ -o testing

$(ODIR)/%.o: $(TDIR)/%.cpp $(HDRS) | $(ODIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(ODIR)/%.o: $(TDIR)/%.cu $(HDRS) | $(ODIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $@

clean:
	rm -rf $(ODIR) a.out testing ray-tracer *.ppm valgrind-out.* vgcore.*
