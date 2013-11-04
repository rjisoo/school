OUTPUT = CS472_HW2_wolfej_coreyg_martich2
TARGET = hw2
SRC = hw2.tex

.PHONY: all
all: default

default: pdf
	mv ${TARGET}.pdf ${OUTPUT}.pdf

.PHONY: dvi
dvi: ${TARGET}.tex
	latex ${TARGET}.tex
	latex ${TARGET}.tex
	

.PHONY: ps
ps: dvi
	dvips -R -Poutline -t letter ${TARGET}.dvi -o ${TARGET}.ps

.PHONY: pdf
pdf: ps
	ps2pdf ${TARGET}.ps


.PHONY: clean
clean:
	rm -f hw2.dvi hw2.aux hw2.log hw2.out
