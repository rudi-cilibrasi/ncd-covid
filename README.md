# ncd-covid
Coronavirus (COVID) genetic analysis using Normalized Compression Distance (NCD)

# Scientific Basis

https://www.biorxiv.org/content/10.1101/2020.07.22.216242v1

Phylogeny of the COVID-19 Virus SARS-CoV-2 by Compression
Paul M B Vitanyi, Rudi L Cilibrasi

The code in this repository was used to make the calculations in the linked
article.

# Downloading Input Data
To retrieve the input data, there are two places you must download:

## MLDSP project data
https://github.com/rudi-cilibrasi/ncd-covid-data

## GISAID data
https://www.gisaid.org/
Researchers must register a free account to download the sequences.

## to test or use,
extract the .fasta files from both sources listed about into a subdirectory
of your choosing and reconfigure the hardcoded paths in this code according to
your directory structure. then build and run the executables in numerical order
to:

```
1. build all .fai files from .fasta files using the fastahack package and the
./scripts/make-fais shell script
2. run the `importer` compiled executable
3. run the `cleaner` compiled executable
4. run the `sort-everything` executable
5. choose any of the tree-* compiled executable experiments to run
```

# Building

```
mkdir build
cd build
cmake ..
make
```

# Data Compressor
Tests run under Ubuntu 20.04

Uses the zpaq (zp) compression utility.


