WD_PATH  := org/openqa/selenium/webkit
SRC_DIR  := src/java
DST_DIR  := build

WD_JAVA  := $(wildcard $(SRC_DIR)/$(WD_PATH)/*.java)
WD_CLASS := $(patsubst $(SRC_DIR)%,$(DST_DIR)%,$(WD_JAVA:.java=.class))

all: wd
	$(MAKE) -C test

wd: $(WD_CLASS)

%.class: %.java
	javac -classpath build:../WebDriver/build/common/common.jar -d $(DST_DIR) $<

.PHONY: all wd
