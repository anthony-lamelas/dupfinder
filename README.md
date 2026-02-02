# dupfinder

Find duplicate files by size and hash.

## Build

```bash
premake5 gmake2
cd build
make config=debug
```

## Run

```bash
./bin/Debug/dupfinder /path/to/search
```

## Tests

Needs Google Test:

```bash
git clone https://github.com/google/googletest.git
cd googletest && mkdir build && cd build
cmake .. && make
cd ../../build
make config=debug dupfinder_tests
../bin/Debug/dupfinder_tests
```

