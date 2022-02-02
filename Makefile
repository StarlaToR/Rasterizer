TARGET?=$(shell $(CXX) -dumpmachine)

BIN=rasterizer
CXXFLAGS=-Wall -Wno-unused-variable -O0 -g
CFLAGS=$(CXXFLAGS)

OBJS=src/main.o src/test.o utils/maths.o
DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: $(BIN)

-include $(DEPS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f $(BIN) $(OBJS) $(DEPS)