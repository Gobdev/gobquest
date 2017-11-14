SRC 	 := src
INCLUDE  := include
BUILD    := build
BIN      := bin

CC       := g++
CFLAGS   := -std=c++14 -I$(INCLUDE) -I /usr/include/
LDFLAGS  := -lboost_system -lboost_filesystem

UNAME    :=$(shell uname)

ifeq ($(UNAME),Linux)
    LDFLAGS += -lncursesw
endif
ifeq ($(UNAME),Darwin)
    LDFLAGS += -lncurses
endif

SRCFILES := $(shell find src/ -name *.cpp)   #All $SRC/.cpp files
OBJFILES := $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(SRCFILES))
DEPFILES := $(patsubst $(SRC)/%.cpp, $(BUILD)/%.d, $(SRCFILES))

PREFIX   := "/usr/local/"

$(BUILD)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/gobquest: $(OBJFILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(OBJFILES) -o $@ $(LDFLAGS)

$(BUILD)/%.d: $(SRC)/%.cpp
	@mkdir -p $(@D)
	@bash ./depend.sh `dirname $<` $(CFLAGS) $< > $@

-include $(DEPFILES)

.PHONY: gobquest
gobquest: $(BIN)/gobquest

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

