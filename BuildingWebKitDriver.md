This page describes how to build the WebKitDriver from source code.

# Supported OS #
WebKitDriver is currenlty only supported on Ubuntu.

# Required Packages #
To be able to build WebKitDriver the following packages need to be availabe on your system. The following lists `apt-get` commands to install them.
```
sudo apt-get install rake
sudo apt-get install bison
sudo apt-get install gperf
sudo apt-get install libcurl3
sudo apt-get install libcurl4-openssl-dev
sudo apt-get install libicu-dev
sudo apt-get install libsqlite3-dev
sudo apt-get install libxslt1-dev
sudo apt-get install libjpeg62-dev
sudo apt-get install libpng12-dev
```

# Building WebKitDriver #
Once you have the above packages installed, do the following to build WebKitDriver.

```
svn checkout http://webkitdriver.googlecode.com/svn/trunk webkitdriver
cd webkitdriver
rake
```

This will do the following:
# Checkout WebKitDriver code, and the WebDriver code (through svn-external dependencies)
# Build libhlwk.so shared library
# Build WebDriver libraries
# Build WebKitDriver libraries
# Run tests.

# Troubleshooting #
## CPP Compilation errors ##
The WebKitDriver build is incremental, that is your build should resume from the point it was interrupted. Occasionaly, when your build is interrupted, the consecutive runs may generate compilation errors. Try this to start a clean build again:
```
rm -rf WebDriver/build
rm -rf hlwk/WebCore/DerivedSources
rm -rf hlwk/JavaScrtipCore/DerivedSources
rake
```




Add your content here.  Format your content with:
  * Text in **bold** or _italic_
  * Headings, paragraphs, and lists
  * Automatic links to other wiki pages