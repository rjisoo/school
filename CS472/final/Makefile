TARGET = final
SRC = $(TARGET).tex
#SRC_PATCH = $(TARGET).patch

default: pdf

.PHONY: dvi
dvi: $(TARGET).tex
	latex $(TARGET)
	bibtex $(TARGET)
	latex $(TARGET)
	latex $(TARGET)

.PHONY: ps
ps: dvi
	dvips -R -Poutline -t letter $(TARGET).dvi -o $(TARGET).ps

.PHONY:pdf
pdf: ps
	ps2pdf $(TARGET).ps

clean:
	@rm -f $(TARGET).aux
	@rm -f $(TARGET).log
	@rm -f $(TARGET).out
	@rm -f $(TARGET).dvi
	@rm -f $(TARGET).ps
	@rm -f $(TARGET).bbl
	@rm -f $(TARGET).blg