# ncd-covid
Coronavirus (COVID) genetic analysis using Normalized Compression Distance (NCD)

# building

```
mkdir build
cd build
cmake ..
make
```

# testing
Tests run under Ubuntu 20.04

Uses the zpaq (zp) compression utility.

Run each of the executables in order:

```
importer
cleaner
```

then any of the ncd calculation utility executables to recreate the
experimental results

