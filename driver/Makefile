WD_DIR   := src/java/org/openqa/selenium/webkit

WD_JAVA  := $(wildcard $(WD_DIR)/*.java)
WD_CLASS := $(WD_JAVA:.java=.class)


all: wd
	$(MAKE) -C test

wd: $(WD_CLASS)

%.class: %.java
	javac -classpath src/java:../build/webdriver-common.jar:../common/src/java $<


.PHONY: all wd
