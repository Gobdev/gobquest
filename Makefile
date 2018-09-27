SRC 	 := src
INCLUDE  := include
BUILD    := build
BIN      := bin
TEST     := tests

CC        := g++
CFLAGS    := -std=c++14 -g -Wall -pedantic -I$(INCLUDE) -I /usr/include/
LDFLAGS   := -lboost_system -lboost_filesystem
TESTFLAGS := -lgtest -lpthread

UNAME    :=$(shell uname)

ifeq ($(UNAME),Linux)
    LDFLAGS += -lncursesw
endif
ifeq ($(UNAME),Darwin)
    LDFLAGS += -lncurses
endif

SRCFILES  := $(shell find $(SRC)/ -name *.cpp)   #All $SRC/.cpp files
OBJFILES  := $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(SRCFILES))
DEPFILES  := $(patsubst $(SRC)/%.cpp, $(BUILD)/%.d, $(SRCFILES))
TESTOBJS  := $(filter-out %/main.o, $(OBJFILES))
TESTFILES := $(shell find $(TEST)/ -name *.cpp)   #All $TEST/.cpp files

PREFIX   := "/usr/local/"

$(BUILD)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/gobquest: $(OBJFILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(OBJFILES) -o $@ $(LDFLAGS)

$(BIN)/gobtest: $(TESTOBJS) $(TESTFILES)
	@mkdir -p $(@D)
	$(info $$TESTOBJS is [${TESTOBJS}])
	$(CC) $(CFLAGS) $(TESTFLAGS) $(TESTFILES) $(TESTOBJS) -o $@ $(LDFLAGS)

$(BUILD)/%.d: $(SRC)/%.cpp
	@mkdir -p $(@D)
	@bash ./depend.sh `dirname $<` $(CFLAGS) $< > $@

-include $(DEPFILES)

.PHONY: gobquest
gobquest: $(BIN)/gobquest

.PHONY: gobtest
gobtest: $(BIN)/gobtest

.PHONY: test
test: $(BIN)/gobtest
	@GOBTEST_DIR=$(TEST) $(BIN)/gobtest --gtest_color=yes

.PHONY: clean
clean:
	@rm -rfv build/
	@rm -rfv bin/

.PHONY: install
install: $(BIN)/gobquest
	@mkdir -p $(DESTDIR)$(PREFIX)/bin
	@mkdir -p $(DESTDIR)$(PREFIX)/gobquest/
	@cp -r games/* $(DESTDIR)$(PREFIX)/gobquest/
	@install $< $(DESTDIR)$(PREFIX)/bin/gobquest

.PHONY: uninstall
uninstall:
	@rm -f $(DESTDIR)$(PREFIX)/bin/gobquest
	@rm -rf $(DESTDIR)$(PREFIX)/gobquest/
