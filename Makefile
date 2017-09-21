all :
	make -C vm/
	make -C asm/
	cp vm/corewar ./
	cp asm/asm ./corewar_asm

 .PHONY : clean fclean

clean :
	make -C vm/ clean
	make -C asm/ clean	

fclean : clean
	make -C vm/ fclean
	make -C asm/ fclean	

re : fclean all
