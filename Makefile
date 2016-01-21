CC := gcc
CFLAGS := -lpthread -lm

VPATH = src:sdk
BUILDDIR = build
BIN = bin

all: checkdirs datagen serialtester main


$(BUILDDIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(BUILDDIR)/path.o $(BUILDDIR)/Lab2IO.o $(BUILDDIR)/utilities.o 
	$(CC) -o $(BIN)/main $^ $(CFLAGS)

datagen: $(BUILDDIR)/Lab2IO.o build/datagen.o
	$(CC) -o $(BIN)/datagen $^

serialtester: build/Lab2IO.o build/serialtester.o 
	$(CC) -o $(BIN)/serialtester $^

checkdirs: $(BUILDDIR) $(BIN)

$(BUILDDIR):
	@mkdir -p $@

$(BIN):
	@mkdir -p $@	

clean:
	rm -rf $(BUILDDIR) 
	rm -rf $(BIN)
	rm -f data_*