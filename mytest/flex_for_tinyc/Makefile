run: word_split
	./word_split < word_split.l

word_split: lex.yy.c
	gcc -o $@ $<

lex.yy.c: word_split.l
	flex $<
