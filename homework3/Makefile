OUTPUT = CS472_HW3_wolfej_coreyg_martich2
TARGET = hw3
SRC = hw3.tex

.PHONY: all
all: default

default: pdf
	mv ${TARGET}.pdf ${OUTPUT}.pdf

.PHONY: dvi
dvi: ${TARGET}.tex
	latex -shell-escape ${TARGET}.tex
	latex -shell-escape ${TARGET}.tex
	

.PHONY: ps
ps: dvi
	dvips -R -Poutline -t letter ${TARGET}.dvi -o ${TARGET}.ps

.PHONY: pdf
pdf: ps
	ps2pdf ${TARGET}.ps


.PHONY: clean
clean:
	rm -f ${TARGET}.dvi 
	rm -f ${TARGET}.aux 
	rm -f ${TARGET}.log 
	rm -f ${TARGET}.out 
	rm -f ${TARGET}.ps
