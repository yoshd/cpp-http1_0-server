SRC_DIR=../src
INC_DIR=../include
TEST_DIR=../test
LIB_DIR=../lib
BIN_DIR=../bin
OBJ_DIR=./obj
GTEST_DIR=../extsrc/googletest/googletest

INCS += -I$(INC_DIR)
INCS += -I$(GTEST_DIR)/include

UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
  CXX=g++
endif
ifeq ($(UNAME),Darwin)
  CXX=g++
endif

CXXFLAGS = -g -Wall
SRCS	 = $(SRC_DIR)/httpresponseheader.cpp $(SRC_DIR)/httpresponse.cpp $(SRC_DIR)/myechoserver.cpp $(SRC_DIR)/httprequestreader.cpp $(SRC_DIR)/httpresponsewriter.cpp $(SRC_DIR)/httprequestparser.cpp $(SRC_DIR)/httprequest.cpp $(SRC_DIR)/httphelper.cpp
TARGET   = $(LIB_DIR)/libhttp.a
LIB_NAME = http
SERVER   = $(BIN_DIR)/httpserver
PORT     = 8080
OBJS     = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))

.PHONY: default
default: $(TARGET)

$(TARGET): $(OBJS)
		@[ -d $(LIB_DIR) ] || mkdir -p $(LIB_DIR)
		$(AR) ruc $(TARGET) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
		@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
		$(CXX) $(CXXFLAGS) $(INCS) -o $@ -c $<


TEST_SRCS = $(TEST_DIR)/httphelpertest.cpp $(TEST_DIR)/httprequestparsertest.cpp $(TEST_DIR)/httpresponseheadertest.cpp $(TEST_DIR)/httpresponsetest.cpp
TEST_TARGET = $(BIN_DIR)/mytest
TEST_OBJS  = $(addprefix $(OBJ_DIR)/, $(notdir $(TEST_SRCS:.cpp=.o)))
LIBS += -L$(LIB_DIR)
LIBS += -l$(LIB_NAME)

CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS = -g -Wall -Wextra -pthread


GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)


$(OBJ_DIR)/gtest-all.o : $(GTEST_SRCS_)
		$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
					-o $@ $(GTEST_DIR)/src/gtest-all.cc

$(OBJ_DIR)/gtest_main.o : $(GTEST_SRCS_)
		$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
					-o $@ $(GTEST_DIR)/src/gtest_main.cc

$(LIB_DIR)/gtest.a : $(OBJ_DIR)/gtest-all.o
		$(AR) $(ARFLAGS) $@ $^

$(LIB_DIR)/gtest_main.a : $(OBJ_DIR)/gtest-all.o $(OBJ_DIR)/gtest_main.o
		$(AR) $(ARFLAGS) $@ $^

.PHONY: check
check: $(TEST_TARGET)
		$(TEST_TARGET)

$(TEST_TARGET): $(TARGET) $(TEST_OBJS) $(LIB_DIR)/gtest_main.a
		@[ -d $(BIN_DIR) ] || mkdir -p $(BIN_DIR)
		$(CXX) $(LDFLAGS) -o $@ $(TEST_OBJS) \
		$(LIB_DIR)/gtest_main.a $(LIBS) -lpthread

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp $(GTEST_HEADERS)
		@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCS) -o $@ -c $<

.PHONY: start-server
start-server: $(SERVER)
		$(SERVER) $(PORT)

$(SERVER): $(TARGET)
		@[ -d $(BIN_DIR) ] || mkdir -p $(BIN_DIR)
		$(CXX) -o $(SERVER) $(LIBS)

.PHONY: clean
clean:
		rm -f $(TARGET) $(TEST_TARGET) $(OBJS) $(TEST_OBJS) $(SERVER)
