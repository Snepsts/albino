# Compiler stuffs
CC = g++
DEBUG = -g
WARNINGS = -Wall
CFLAGS = -c# Leave this almost blank bc it is prepended in every target
LFLAGS =# Leave this blank bc it is prepended in every target
OFLAGS = -O2
EXFLAGS = $(NCURSES)
NCURSES = -lncurses

# Partitioning
SRCDIR = src
BUILDDIR = build
TARGET = albino.out

# Finding files
SRCEXT = cpp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Build stuffs
PREFIX = [Makefile]:
LINK = $(CC) $(LFLAGS) $^ -o $(TARGET) $(EXFLAGS)# For linking build
COMPILE = $(CC) $(CFLAGS) -o $@ $< $(EXFLAGS)# For compiling build
COMPILE_MSG = Compiling $< # For communicating what is being built
CLEAN = $(RM) -r $(BUILDDIR) $(TARGET) # For cleaning up (if it wasn't obvious)

# Debug prepends warnings/debug flags
# This is the default target, it is for most cases
debug: CFLAGS += $(WARNINGS) $(DEBUG)
debug: LFLAGS += $(WARNINGS) $(DEBUG)
debug: $(OBJECTS)
	@echo "*\n*\n*\n You have compiled the debug build. \n*\n*\n*"
	@echo "$(PREFIX) Linking..."
	@echo "$(PREFIX) $(LINK)"; $(LINK)

# Test prepends optimizations and warnings to the build
# Use this when you're preparing to put the build up for redistribution
test: CFLAGS += $(WARNINGS) $(OFLAGS)
test: LFLAGS += $(WARNINGS) $(OFLAGS)
test: $(OBJECTS)
	@echo "*\n*\n*\n You have compiled the test build. \n*\n*\n*"
	@echo "$(PREFIX) Linking..."
	@echo "$(PREFIX) $(LINK)"; $(LINK)

# Release prepends optimizations to the build and nothing more
# Use this when you're putting
release: CFLAGS += $(OFLAGS)
release: LFLAGS += $(OFLAGS)
release: $(OBJECTS)
	@echo "*\n*\n*\n You have compiled the release build. \n*\n*\n*"
	@echo "$(PREFIX) Linking..."
	@echo "$(PREFIX) $(LINK)"; $(LINK)

# Rules for all of the objects to build
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR) # Make the directory if it doesn't exist
	@echo "$(PREFIX) $(COMPILE_MSG)";
	$(COMPILE)

# Removes all files so the next build is a "clean" build
clean:
	@echo "$(PREFIX) Cleaning...";
	@echo "$(PREFIX) $(CLEAN)"; $(CLEAN)
