BUILD = ../build
CFLAGS = -w  -g -I../includes

# Get all .c files in the current directory
SRC = $(wildcard *.c)
EXCLUDE = 

# Convert .c files to .o files
SRC := $(filter-out $(EXCLUDE), $(SRC))
OBJ = $(SRC:.c=.o)

# Default rule
all: $(OBJ)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(BUILD)/$@

# Clean rule
clean:
	rm -f $(patsubst %.c, $(BUILD)/%.o, $(SRC))

# # Major Definitions
# # =================


# STANDARD_OBJ= acceler.o  ceval.o \
# 		compile.o errors.o fgetsintr.o \
# 		graminit.o grammar1.o import.o \
# 		intrcheck.o listnode.o modsupport.o \
# 		node.o object.o parser.o parsetok.o regexp.o \
# 		strdup.o structmember.o \
# 		tokenizer.o traceback.o \
# 		$(STRTOL_OBJ) $(STRERROR_OBJ) \
# 		$(FMOD_OBJ) $(GETCWD_OBJ) \
		
		


# STANDARD_SRC= acceler.c  ceval.c\
# 		compile.c  errors.c fgetsintr.c \
# 		graminit.c grammar1.c import.c \
# 		intrcheck.c listnode.c modsupport.c \
# 		node.c object.c  regexp.c \
# 		strdup.c structmember.c \
# 		tokenizer.c traceback.c \
#
# 		parser.c parsetok.c



# fgetsintr.o:	fgetsintr.c
# 		$(COMPILE) $*.c

# intrcheck.o:	intrcheck.c
# 		$(COMPILE) $*.c


# GENSOURCES=	acceler.c fgetsintr.c grammar1.c \
# 		intrcheck.c listnode.c node.c parser.c \
# 		parsetok.c strdup.c tokenizer.c bitset.c \
# 		firstsets.c grammar.c metagrammar.c pgen.c \
# 		pgenmain.c printgrammar.c object.c

# GENOBJECTS=	acceler.o fgetsintr.o grammar1.o \
# 		intrcheck.o listnode.o node.o parser.o \
# 		parsetok.o strdup.o tokenizer.o bitset.o \
# 		firstsets.o grammar.o metagrammar.o pgen.o \
# 		pgenmain.o printgrammar.o object.o

# python_gen:	$(GENOBJECTS)
# 		$(CC) $(CFLAGS) $(GENOBJECTS) -o python_gen