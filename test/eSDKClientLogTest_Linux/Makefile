# ver = debug // make debug
# ver = release // make release
# Change ver When Need before Making

export CPATH=../../source/eSDKClientLog/output/include

ver = debug
#ver = release 
CXX = g++
ifeq ($(ver), debug)
CXXFLAGS = -O -g -w 
else
CXXFLAGS = -O2 -w
endif

OBJS = test.cpp	
LIB = eSDKLogAPI
ifeq ($(ver), debug)
LIBDIR = ../../source/eSDKClientLog/output/debug_linux
TARGET = $(LIBDIR)/eSDKLogAPI_Test_Debug
else
LIBDIR = ../../source/eSDKClientLog/output/release_linux
TARGET = $(LIBDIR)/eSDKLogAPI_Test_Release
endif
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^ -l $(LIB) -L $(LIBDIR) 
.PHONY: clean
clean:
	-rm -f $(TARGET)
