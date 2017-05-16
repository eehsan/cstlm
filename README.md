Welcome to CSTLM
================

This is a compressed suffix tree based infinite context size language model capable of indexing terabyte sized text collections.

## References

This code is the basis of the following papers:

- Ehsan Shareghi, Matthias Petri, Gholamreza Haffari, Trevor Cohn: Compact, Efficient and Unlimited Capacity: Language Modeling with Compressed Suffix Trees. EMNLP 2015: 2409-2418

- Ehsan Shareghi, Matthias Petri, Gholamreza Haffari, Trevor Cohn: Fast, Small and Exact: Infinite-order Language Modelling with Compressed Suffix Trees. TACL 2016 : 477-490

- Ehsan Shareghi, Trevor Cohn, Gholamreza Haffari: Richer Interpolative Smoothing Based on Modified Kneser-Ney Language Modeling. EMNLP 2016: 944-948

Please cite our EMNLP2015 and TACL2016 papers, if you use our code. 

## Compile instructions

1. Check out the reprository: `https://github.com/eehsan/cstlm.git`
2. `git submodule update --init`
3. `cd build`
4. `cmake ..`
5. `make -j`

## Run unit tests to ensure correctness

```
cd build
rm -rf ../collections/unittest/
./create-collection.x -i ../UnitTestData/data/training.data -c ../collections/unittest
./create-collection.x -i ../UnitTestData/data/training.data -c ../collections/unittest -1
./unit-test.x
```

## Usage instructions (Word based language model)

Create collection:

```
./create-collection.x -i toyfile.txt -c ../collections/toy
```

Build index (including quantities for modified KN)

```
./build-index.x -c ../collections/toy/ -m
```

Query index (i.e., Modified KN (drop -m for KN), 5-gram)

```
./query-index-knm.x -c ../collections/toy/ -p test.txt -m -n 5 
```
## Usage instructions (Character based language model)

Create collection:

```
./create-collection.x -i toyfile.txt -c ../collections/toy -1
```

Build index (including quantities for modified KN)

```
./build-index.x -c ../collections/toy/ -m
```

## Generalized Modified Kneser-Ney

- Check out the MMKN branch of the repository: `https://github.com/eehsan/cstlm.git`

## Moses integration
Checkout what Matthias has developed on [his repository](https://github.com/mpetri/cstlm).
