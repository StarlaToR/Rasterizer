TARGET?=$(shell $(CXX) -dumpmachine)

BIN=rasterizer
CXXFLAGS=-Wall -Wno-unused-variable -O0 -g
CFLAGS=$(CXXFLAGS)
#CPPFLAGS=-Iexternals/include -MMD
#LDFLAGS=-Lexternals/libs-$(TARGET)

OBJS=src/main.o utils/maths.o
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