CFLAGS = -O3 -W -Wall -g

SRC_MANDEL=mandel/mandel_simple/mandel.cpp
SRC_JULIA=julia/julia_simple/julia.cpp

SRC_MANDEL_E=mandel/mandel_explorer/mandel_explorer.cpp
SRC_JULIA_E=julia/julia_explorer/julia_explorer.cpp

SRC_TREE=tree/tree.cpp

INCLUDES=-I includes/
LIBS_SRC=includes/fractal_math.cpp includes/quickcg.cpp
LIBS=-lSDL

TARGET_M=bin/mandel
TARGET_J=bin/julia
TARGET_ME=bin/mandel_explorer
TARGET_JE=bin/julia_explorer
TARGET_TREE=bin/tree

.PHONY: all
all: $(TARGET_M) $(TARGET_J) $(TARGET_ME) $(TARGET_JE) $(TARGET_TREE)

.PHONY: mandel
mandel: $(TARGET_M)

.PHONY: julia
julia: $(TARGET_J)

.PHONY: mandel_exp
mandel_exp: $(TARGET_ME)

.PHONY: julia_exp
julia_exp: $(TARGET_JE)

.PHONY: tree
tree: $(TARGET_TREE)


$(TARGET_M):
	g++ $(CFLAGS) $(SRC_MANDEL) $(LIBS_SRC) $(LIBS) $(INCLUDES) -o $@

$(TARGET_J):
	g++ $(CFLAGS) $(SRC_JULIA) $(LIBS_SRC) $(LIBS) $(INCLUDES) -o $@

$(TARGET_ME):
	g++ $(CFLAGS) $(SRC_MANDEL_E) $(LIBS_SRC) $(LIBS) $(INCLUDES) -o $@

$(TARGET_JE):
	g++ $(CFLAGS) $(SRC_JULIA_E) $(LIBS_SRC) $(LIBS) $(INCLUDES) -o $@

$(TARGET_TREE):
	g++ $(CFLAGS) $(SRC_TREE) $(LIBS_SRC) $(LIBS) $(INCLUDES) -o $@

.PHONY: clean
clean:
	rm -rf bin/*
