OUTPUT = CS472_Midterm2_coreyg
TARGET = midterm2
SRC = $(TARGET).tex

.PHONY: all
all: default

default: pdf

# 	mewo meow meow

.PHONY: dvi
dvi: $(TARGET).tex
	latex -shell-escape $(TARGET).tex
	latex -shell-escape ${TARGET}.tex
	

.PHONY: ps
ps: dvi
	dvips -R -Poutline -t letter $(TARGET).dvi -o $(TARGET).ps

.PHONY: pdf
pdf: ps
	ps2pdf $(TARGET).ps $(OUTPUT).pdf


.PHONY: clean
clean:
	rm -f $(TARGET).dvi 
	rm -f $(TARGET).aux 
	rm -f $(TARGET).log 
	rm -f $(TARGET).out 
	rm -f $(TARGET).ps
	rm -f *.pyg
