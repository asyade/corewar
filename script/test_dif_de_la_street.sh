#!/bin/bash
for filename in champion/*.cor; do
	for filename2 in champion/*.cor; do
			echo $filename $filename2
    		export i=10000; while [ $i -le 20000 ] ; do ./test_diff_2v2_dump  $filename  $filename  $((i+=10000)); done
	done
done