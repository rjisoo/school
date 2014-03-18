TARGET = final
SRC = final.tex

.PHONY: all
all: default

default: pdf

.PHONY: dvi
dvi: $(TARGET).tex
	latex $(TARGET).tex
#	bibtex $(TARGET).aux
#	latex $(TARGET).tex
	latex $(TARGET).tex
	

.PHONY: ps
ps: dvi
	dvips -R -Poutline -t letter $(TARGET).dvi -o $(TARGET).ps

.PHONY: pdf
pdf: ps
	ps2pdf $(TARGET).ps

.PHONY: clean
clean:
	@rm -f $(TARGET).dvi
	@rm -f $(TARGET).ps
	@rm -f $(TARGET).log
	@rm -f $(TARGET).aux
	@rm -f $(TARGET).out
	@rm -f $(TARGET).b*
