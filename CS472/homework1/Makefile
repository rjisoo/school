TARGET = hw1
SRC = hw1.tex

.PHONY: all
all: default

default: pdf

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
