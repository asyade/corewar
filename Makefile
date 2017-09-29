all :
	make -C vm/
	make -C assembleur/
	cp vm/corewar ./
	cp assembleur/asm ./

 .PHONY : clean fclean

clean :
	make -C vm/ clean
	make -C assembleur/ clean	
	@rm		asm
	@rm		corewar

fclean : clean
	make -C vm/ fclean
	make -C assembleur/ fclean	

re : fclean all
