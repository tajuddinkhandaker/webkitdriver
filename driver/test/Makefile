NAME  := Example
SRC   := $(NAME).java
CLASS := $(NAME).class

LIBPATH   := ../../hlwk/WebKitBuild/Release
CLASSPATH := ../../WebDriver/build/webdriver_hlwk.jar:../../WebDriver/build/java/client/src/org/openqa/selenium/base.jar:../../WebDriver/build/java/client/src/org/openqa/selenium/webdriver-api.jar:../../third_party/java/guava/guava-r05.jar:../../WebDriver/third_party/java/junit/junit-dep-4.8.1.jar

all: $(CLASS)

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

.PHONY: all run debug
