BUILD = ../build
CFLAGS = -w -g -I../includes

# Get all .c files in the current directory
SRC = $(wildcard *.c)
EXCLUDE = metagrammar.c profmain.c


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
