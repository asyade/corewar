#!/bin/zsh
make && find champs_test -type f -iname "*.s" -print0 |
while IFS= read -r -d $'\0' test;
do
	echo "----$test----";
	echo -n "$test" | cut -f 2- -d "/" | read test;
	./asm ./champs_test/"$test" ;
	./asm_test ./champs_test_bin/"$test";
	echo "$test" | cut -f 1 -d "."| read test;
	cat ./champs_test/"$test".cor > diff &&
	cat ./champs_test_bin/"$test".cor > diff_bin &&
	diff diff diff_bin;
	echo "_______END_TEST_______";
done
