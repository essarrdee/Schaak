# Generic Makefile v0.1 by Mike Kasprzak (http://toonormal.com)
# Adapted for Schaak by Michał Walczak (http://michalwalczak.eu)
# usage: make | make info | make clean | make run
# - ------------------------------------------------------------------------ - #
TARGET_FILE     :=  schaakgame
ARGS            :=  
# - ------------------------------------------------------------------------ - #
 
# - ------------------------------------------------------------------------ - #
# Symbols (macros) to define ### e.g. USES_SOMETHING SOME_TEXT="Hello"
DEFINES         :=
# - ------------------------------------------------------------------------ - #
 
# - ------------------------------------------------------------------------ - #
# Path to individual source files ### e.g. Engine/Main.cpp Game/Player.c
SRC_FILES       :=	main.cpp \
					Board.cpp \
					ChessSet.cpp \
					Game.cpp \
					Interface.cpp \
					Logger.cpp \
					MenuSystem.cpp \
					Piece.cpp \
					PieceManager.cpp \
					PieceType.cpp \
					Behaviour.cpp \
					BehaviourManager.cpp \
# - ------------------------------------------------------------------------ - #
# Folders to search for source files ### e.g. zlib zlib/extras squirrel
SRC_FOLDERS     :=  
# - ------------------------------------------------------------------------ - #
# Enable to assume all files are found in a "src/" subfolder (src/myfile.c)
#SRC_PREFIX     :=  src/
# - ------------------------------------------------------------------------ - #
 
# - ------------------------------------------------------------------------ - #
# Base directories to search for include files ### e.g. zlib squirrel/include
INCLUDE_DIRS    :=  ./
# - ------------------------------------------------------------------------ - #
# Base directories to search for library files ### e.g. /usr/local/lib mylibs
LIBRARY_DIRS    :=  
# - ------------------------------------------------------------------------ - #
# Library Files to include, with -l ### e.g. -liberty -lsdl_mixer
LIBRARY_FILES   :=  -lsfml-graphics -lsfml-system -lsfml-window
# - ------------------------------------------------------------------------ - #
 
# - ------------------------------------------------------------------------ - #
# Compiler Flags ### e.g. --std=gnu++0x -fno-rtti -fno-strict-aliasing
FLAGS           :=	-std=c++11 -I. -Wall
C_FLAGS         :=  $(FLAGS)
CPP_FLAGS       :=  $(FLAGS)
# - ------------------------------------------------------------------------ - #
# Linker Flags ### e.g. -static-libgcc -static-libstdc++ -static -mwindows
LD_FLAGS        :=
# - ------------------------------------------------------------------------ - #
 
# - ------------------------------------------------------------------------ - #
SRC_FILE_TYPES  :=  .c .cpp
# - ------------------------------------------------------------------------ - #
ALL_SRC_FILES   :=  $(wildcard $(addprefix $(SRC_PREFIX),$(addsuffix /*,$(SRC_FOLDERS))))
SRC_FILES       :=  $(addprefix $(SRC_PREFIX),$(SRC_FILES)) \
                    $(filter $(addprefix %,$(SRC_FILE_TYPES)),$(ALL_SRC_FILES))
# - ------------------------------------------------------------------------ - #
DEFINES         :=  $(addprefix -D,$(DEFINES))
INCLUDE_DIRS    :=  $(addprefix -I$(SRC_PREFIX),$(INCLUDE_DIRS))
LIBRARY_DIRS    :=  $(addprefix -L,$(LIBRARY_DIRS))
# - ------------------------------------------------------------------------ - #
# Where out files will output #
OUTPUT_DIR      :=  ./
OBJ_DIR         :=  obj/
# - ------------------------------------------------------------------------ - #
TARGET          :=  $(OUTPUT_DIR)$(TARGET_FILE)
# - ------------------------------------------------------------------------ - #
O_FILES         :=  $(addprefix $(OBJ_DIR),$(addsuffix .o,$(SRC_FILES)))
# - ------------------------------------------------------------------------ - #
O_DIRS          :=  $(sort $(dir $(O_FILES)))
# - ------------------------------------------------------------------------ - #
# Commands for Compiling C code, C++ code, and Linking #
CC              :=  gcc
CXX             :=  g++
LD              :=  $(CXX)
# NOTE: Using the C++ compiler for linking instead of ld because it's simpler. #
# - ------------------------------------------------------------------------ - #
RUN             :=  ./$(TARGET) $(ARGS)
# - ------------------------------------------------------------------------ - #
 
 
# - ------------------------------------------------------------------------ - #
# Link Command #
# - ------------------------------------------------------------------------ - #
$(TARGET): _makedirs $(O_FILES)
	$(LD) $(LD_FLAGS) $(LIBRARY_DIRS) $(O_FILES) $(LIBRARY_FILES) -o $@
# - ------------------------------------------------------------------------ - #
 
# - ------------------------------------------------------------------------ - #
# Compile Commands #
# - ------------------------------------------------------------------------ - #
$(OBJ_DIR)%.c.o: %.c
	$(CC) -c $(DEFINES) $(INCLUDE_DIRS) $(C_FLAGS) $< -o $@
# - ------------------------------------------------------------------------ - #
$(OBJ_DIR)%.cpp.o: %.cpp
	$(CXX) -c $(DEFINES) $(INCLUDE_DIRS) $(CPP_FLAGS) $< -o $@
# - ------------------------------------------------------------------------ - #
 
 
# - ------------------------------------------------------------------------ - #
_makedirs:
	mkdir -p $(O_DIRS) $(OUTPUT_DIR)
# - ------------------------------------------------------------------------ - #
clean:
	rm -fr $(OBJ_DIR) $(OUTPUT_DIR)$(TARGET_FILE)
# - ------------------------------------------------------------------------ - #
run:
	$(RUN)
# - ------------------------------------------------------------------------ - #
info:
	@echo TARGET_FILE: $(TARGET_FILE) [$(TARGET)]
	@echo
	@echo SRC_FILES: $(SRC_FILES)
	@echo
	@echo O_FILES: $(O_FILES)
	@echo
	@echo O_DIRS: $(O_DIRS)
# - ------------------------------------------------------------------------ - #
.PHONY: _makedirs clean run info
# - ------------------------------------------------------------------------ - #