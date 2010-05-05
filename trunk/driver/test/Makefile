NAME  := Example
SRC   := $(NAME).java
CLASS := $(NAME).class

#LIBPATH   := ../../third_party/hlwk/WebKitBuild/Debug
LIBPATH   := ../../third_party/hlwk/WebKitBuild/Release
CLASSPATH := ../src/java:../../build/webdriver-common.jar

$(CLASS): $(SRC)
	javac -classpath $(CLASSPATH) $(SRC)

debug: $(CLASS)
	WEBKIT_DEBUG=NotYetImplemented LD_LIBRARY_PATH=$(LIBPATH) java -classpath .:$(CLASSPATH) $(NAME)

run: $(CLASS)
	LD_LIBRARY_PATH=$(LIBPATH) java -classpath .:$(CLASSPATH) $(NAME)

%.class: %.java
	javac -classpath $(CLASSPATH) $<

run-%: %.class
	LD_LIBRARY_PATH=$(LIBPATH) java -classpath .:$(CLASSPATH) $*

.PHONY: run
