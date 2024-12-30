SOURCE = parser.c
EXE = $(SOURCE:.c=.exe)

all: $(EXE)

%.exe: %.c
	$(CC) $< -o $@

run: all
	./$(EXE)

clean_run: clean run
.PHONY: clean_run

clean:
	rm -f $(wildcard $(EXE))
# @echo rm $(EXE)
# @if [ -f "$(EXE)" ]; then rm $(EXE); fi
# -rm $(EXE) >/dev/null 2>&1
# we cant put &> /dev/null becasue make supports only sh syntex not bash
# .SILENT: clean
# .IGNORE: clean