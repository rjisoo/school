TARGET = project1
SRC = project1.tex
SRC_PATCH = ${TARGET}.patch

default: pdf

.PHONY: dvi
dvi: ${TARGET}.tex
	pygmentize -f latex -o __${SRC_PATCH}.tex ${SRC_PATCH}
	latex ${TARGET}
	latex ${TARGET}

.PHONY: ps
ps: dvi
	dvips -R -Poutline -t letter ${TARGET}.dvi -o ${TARGET}.ps

.PHONY:pdf
pdf: ps
	ps2pdf ${TARGET}.ps

clean:
	@rm -f ${TARGET}.aux
	@rm -f ${TARGET}.log
	@rm -f ${TARGET}.out
	@rm -f ${TARGET}.dvi
	@rm -f ${TARGET}.ps
	@rm -f __project1.patch.tex
