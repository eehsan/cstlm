Welcome to CSTLM
================

This is a compressed suffix tree based infinite context size language model capable of indexing terabyte sized text collections.

## References

This code is the basis of the following paper:

- Ehsan Shareghi, Trevor Cohn, Gholamreza Haffari: Richer Interpolative Smoothing Based on Modified Kneser-Ney Language Modeling. EMNLP 2016: 944-948

Please cite our EMNLP2016 paper, if you use our code. 

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

Query index (i.e., Modified KN (drop -m for KN), 5-gram, discount_depth 5)

```
./query-index-knm.x -c ../collections/toy/ -p test.txt -m -n 5  -d 5
``
