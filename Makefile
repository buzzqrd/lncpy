
TARGET=lncpy
INSTALL_PATH=/usr/bin/
CCOMPILER=cc

SOURCES=lncpy.c

all: $(SOURCES)
	$(CCOMPILER) $(SOURCES) -o $(TARGET)

install:
	$(CCOMPILER) $(SOURCES) -o $(TARGET)
	cp $(TARGET) $(INSTALL_PATH)
	
uninstall:
	rm -f $(INSTALL_PATH)$(TARGET)

clean:
	rm -f $(TARGET)


