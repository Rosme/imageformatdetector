# Image Format detector

The IFD is a simple C++ program that uses magic number and extension to figure out the format of an image file.

## Requirements

  * Valid C++11 compiler
  * cmake 2.6+

## Building

```
cmake && make
```

The executable should be in the bin directory

## Usage

```
./bin/ImageFormatDetector <PathToImage>
```
