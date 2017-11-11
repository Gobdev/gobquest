SRC 	 := src
INCLUDE  := include
BUILD    := build
BIN      := bin

CC       := g++
CFLAGS   := -std=c++14 -I$(INCLUDE) -I /usr/include/
LDFLAGS  := -lpqxx -lpq -lncursesw -lboost_system -lboost_filesystem

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

-include $(DEPFILES)

$(BUILD)/%.d: $(SRC)/%.cpp
	@mkdir -p $(@D)
	@bash ./depend.sh `dirname $<` $(CFLAGS) $< > $@

.PHONY: gobquest
config_tool: $(BIN)/config_tool

.PHONY: clean
clean:
	@rm -rfv build/
	@rm -rfv bin/

PREFIX = /usr/local

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

