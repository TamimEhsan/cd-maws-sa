
# change directory
cd ../cd-maws-sa
# compile the code
g++ -O2 -o maw-gen maw-gen.cpp
g++ -O2 -o dist-calc dist-calc.cpp

# change directory
cd ../cd-maws-sa-enc
# compile the code
g++ -O2 -o maw-gen-enc maw-gen-enc.cpp
g++ -O2 -o dist-calc-enc dist-calc-enc.cpp
