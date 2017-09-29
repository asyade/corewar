all :
	make -C vm/
	make -C assembleur/
	cp vm/corewar ./
	cp assembleur/asm ./

 .PHONY : clean fclean

clean :
	make -C vm/ clean
	make -C assembleur/ clean	

fclean : clean
	make -C vm/ fclean
	make -C assembleur/ fclean	
	rm -f asm
	rm -f corewar

re : fclean all
