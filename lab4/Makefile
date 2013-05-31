OUTPUT = CS472_Lab4_wolfej_coreyg_martich2
TARGET = lab4
SRC = lab4.tex

.PHONY: all
all: default

default: pdf

# 	mewo meow meow

.PHONY: dvi
dvi: ${TARGET}.tex
	latex -shell-escape ${TARGET}.tex
	latex -shell-escape ${TARGET}.tex
	

.PHONY: ps
ps: dvi
	dvips -R -Poutline -t letter ${TARGET}.dvi -o ${TARGET}.ps

.PHONY: pdf
pdf: ps
	ps2pdf ${TARGET}.ps ${OUTPUT}.pdf


.PHONY: clean
clean:
	rm -f ${TARGET}.dvi 
	rm -f ${TARGET}.aux 
	rm -f ${TARGET}.log 
	rm -f ${TARGET}.out 
	rm -f ${TARGET}.ps
	rm -f *.pyg part1/*.pyg part2/*.pyg
	

.PHONY: c
c:
	gcc main.c -o main
