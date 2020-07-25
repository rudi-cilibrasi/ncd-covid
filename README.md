# ncd-covid
Coronavirus (COVID) genetic analysis using Normalized Compression Distance (NCD)

# scientific basis

https://www.biorxiv.org/content/10.1101/2020.07.22.216242v1
Phylogeny of the COVID-19 Virus SARS-CoV-2 by Compression
Paul M B Vitanyi, Rudi L Cilibrasi

The code in this repository was used to make the calculations in the linked
article.

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

