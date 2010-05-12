NAME  := Example
SRC   := $(NAME).java
CLASS := $(NAME).class

#LIBPATH   := ../../third_party/hlwk/WebKitBuild/Debug
LIBPATH   := ../../hlwk/WebKitBuild/Release
CLASSPATH := ../src/java:../../WebDriver/build/common/common.jar

$(CLASS): $(SRC)
	javac -classpath $(CLASSPATH) $(SRC)

debug: $(CLASS)
	WEBKIT_DEBUG=StorageAPI LD_LIBRARY_PATH=$(LIBPATH) java -classpath .:$(CLASSPATH) $(NAME)

run: $(CLASS)
	LD_LIBRARY_PATH=$(LIBPATH) java -classpath .:$(CLASSPATH) $(NAME)

%.class: %.java
	javac -classpath $(CLASSPATH) $<

run-%: %.class
	LD_LIBRARY_PATH=$(LIBPATH) java -classpath .:$(CLASSPATH) $*

.PHONY: run
