# CD-MAWS-SA
This repository contains the official implementation of the abstract An Efficient Implementation of Cosine Distance
on Minimal Absent Word Sets using Suffix
Automata.

## Brief Description 
We have modified the paper CD-MAWS: A phylogenetic tree construction tool using Cosine Distance on Minimal Absent Word (MAW). 

The improvement is done in two parts:

**1. MAW Generation:** The original paper relied on library [solonas13/maw](https://github.com/solonas13/maw) developed by C. Barton et al. We proposed another algorithm using Suffix Automaton to find the maw set. A nice outcome of our approach is the maw set generated are in sorted order. 

**2. Distance Calculation:** The original CD-MAWS used a augmented vector approach to find the distances. The approach though easy to understand, increases the time and space complexity. Instead of creating the vector we used a simple two pointer based approach on the sorted maw set to find the distance.

## Running the codes

### Data generation
In order to generate the data,  we used PASTA algorithm to generate a phylogenetic tree in Newick format (with branch lengths) and the Seq-gen Monte Carlo simulation tool to generate DNA sequences from that tree. The PASTA tool takes a fasta file as input and produces a tree as output. To create the tree on the 1000L2 R0 dataset from the SATe paper, we have used the following command:

```bash
python run pasta.py -i rose.aln.true.fasta
```
Here, `rose.aln.true.fasta` is the fasta file for the 1000L2 R0 dataset. To generate a set of 1000
sequences, each consisting of 2000 base pairs, from the output tree of the PASTA tool, we have
used the following command of the Seq-gen tool:

```bash
seq-gen -mGTR -r0.25, 1, 4, 4, 1.380952381, 0.3452380952 -l2000 -n1
-s1.0 -or input.tree out.phy 
```
### Maw generation
Use the data generated in the previous stage as input to this stage. At first compile the `src/maw-gen.cpp` file and then execute it.

```bash
g++ -o maw-gen maw-gen.cpp
maw-gen <species-file> <generated-maw-file> <minK> <maxK>
```
### Distance calculation
Use the maw set generated in the previous stage as input to this stage. 

```bash
g++ -o dist-cal dist-calc.cpp
dist-calc <generated-maw-file> <distance-file>
```


## License

The contents of this repository are licensed under the MIT License.

See LICENSE for the full license text.

## Bugs or Issues

We are constantly searching for ways to improve our codebase.

For any bugs, please post on issues page.

Alternatively, you can email at tamimehsan99@gmail.com.