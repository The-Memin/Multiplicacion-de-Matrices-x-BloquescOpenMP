#!/bin/bash
 for k in 2 4 8
	 do
	     for i in 64 128 256 512 1024
	      do
          for (( c=0; c<=2; c++ ))
            do  
                ./openmp $i $k
            done
	      done
	 done
mkdir archivos
mv *.txt archivos