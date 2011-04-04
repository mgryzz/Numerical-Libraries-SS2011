TEX_FILES=$(wildcard *.tex)
TARGET=report

$(TARGET).ps: $(TARGET).dvi $(wildcard *.eps)
	dvips  $(TARGET) -o
	ps2pdf $(TARGET).ps

$(TARGET).bbl $(TARGET).aux: $(TARGET).bib 
	# ensure we make a .aux file
	latex $(TARGET)
	# use the .aux file
	bibtex $(TARGET)
	# rerun to fix up the .aux file
	latex $(TARGET)

$(TARGET).dvi: $(TEX_FILES) $(TARGET).bbl $(TARGET).aux
	latex $(TARGET) 
	latex $(TARGET) 

clean: 
	rm -f *~ *bak *.{toc,aux,ps,log,lof,bbl,blg,dvi,pdf}

.PHONY: clean
