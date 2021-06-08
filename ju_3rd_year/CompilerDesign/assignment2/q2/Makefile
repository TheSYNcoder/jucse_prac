
calculator : 
	yacc -d cal.y
	lex cal.l
	gcc -o $@ lex.yy.c y.tab.c
	./$@
	

.PHONY: clean

# ~ means to ignore all the warings if file is not present

clean:
	rm -f *~ core $(INCDIR)/*~ 
	rm lex.yy.c y.tab.c y.tab.h
	rm -f calculator
