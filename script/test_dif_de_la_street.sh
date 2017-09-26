#!/bin/bash
for filename in champion/*.cor; do
		echo $filename
    	export i=100; while [ $i -le 4000 ] ; do ./test_diff_2v2_dump  $1  $filename  $((i+=1000)); done
done