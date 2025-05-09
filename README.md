﻿# CD-MAWS-SA
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

### Dataset from AF Project

Download biological dataset from [AFproject](https://afproject.org/app/). The datasets used to benchmark are

| Dataset | Number of Species | Total Sequence Size (MB) |
| :-  | :-: | :-: |
| Fish mtDNA | 25 | 0.42 |
| E.coli/Shigella | 29 | 144.3 |
| E.coli/Shigella (HGT) | 27 | 134.70 |
| Yersinia (HGT) | 8 | 37.50 |
| Simulated (HGT) | 33 | 74.40 |

Download the dataset and put them in a folder `/benchmark/data/dataset-name/input`
After downloading and extracting data, the folder might look something like this
```
CD-MAWS-SA
├── benchmark
│   └── data
│       ├── assembled-ecoli
│       │   ├── input
│       │   │   ├── 536.fasta
│       │   │   ├── APEC01.fasta
│       │   │   ├── ATCC8739.fasta
```
### Compilation

You need to compile the source codes at first. You can compile and create executables one by one using
```sh
cd <folder>
g++ -O2 -o <out_file_name> <file_name>.cpp
```
Or you can create all of the executables by running the script file
```
cd scripts
chmod +x generate_executables.sh
./generate_executables.sh
```

### Maw generation
There 3 ways you can generate maws

#### MAW generation by Barton 
Use the data generated in the previous stage as input to this stage. If the dataset is in a single file, then running the following command is enough.

```bash
./cd-maws/maw <species-fasta-file> <maw-file> <minK> <maxK>
```
If the dataset is divided into multiple files, you can concat them in a single file and then run the above command. Another way is to run a script file. Make sure the input and output folders are set properly.
```bash
cd scripts
chmod +x generate_maw_barton.sh
./generate_maw_barton.sh
```

#### MAW generation by CD-MAWS-SA 
Use the data generated in the previous stage as input to this stage. 

```bash
./cd-maws-sa/maw-gen <species-fasta-file> <maw-file> <minK> <maxK>
```

If the dataset is divided into multiple files, you can concat them in a single file and then run the above command. Another way is to run a script file. Make sure the input and output folders are set properly.
```bash
cd scripts
chmod +x generate_maw_cd_maws_sa.sh
./generate_maw_cd_maws_sa.sh
```
#### MAW generation by CD-MAWS-SA-ENC
Use the data generated in the previous stage as input to this stage. 

```bash
./cd-maws-sa-enc/maw-gen-enc <species-fasta-file> <maw-file> <minK> <maxK>
```

If the dataset is divided into multiple files, you can concat them in a single file and then run the above command. Another way is to run a script file. Make sure the input and output folders are set properly.
```bash
cd scripts
chmod +x generate_maw_cd_maws_sa_enc.sh
./generate_maw_cd_maws_sa_enc.sh
```

### Distance calculation
Use the maw set generated in the previous stage as input to this stage. 

#### Distance calculation by CD-MAWS
```bash
./cd-maws/main -i <maw-file> -o <distance_matrix_file> 
```

#### Distance calculation by CD-MAWS-SA
```bash
./cd-maws-sa/dist-calc -i <maw-file> <distance_matrix_file>
```

#### Distance calculation by CD-MAWS-SA-ENC
```bash
./cd-maws-sa-enc/dist-calc-enc -i <maw-file> <distance_matrix_file> 
```

## License

The contents of this repository are licensed under the MIT License.

See LICENSE for the full license text.

## Bugs or Issues

We are constantly searching for ways to improve our codebase.

For any bugs, please post on issues page.

Alternatively, you can email at tamimehsan99<at>gmail<dot>com.

## Citing

If you used this, consider citing the following paper:
```
@inproceedings{ehsan2025efficient,
  title={An Efficient Implementation of Cosine Distance on Minimal Absent Word Sets Using Suffix Automata},
  author={Ehsan, Mohammad Tamimul and Mosaddek, Sk Sabit Bin and Rahman, M Saifur},
  booktitle={International Conference and Workshops on Algorithms and Computation},
  pages={180--195},
  year={2025},
  organization={Springer}
}
```
