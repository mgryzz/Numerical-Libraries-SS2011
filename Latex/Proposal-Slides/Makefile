TARGET=slides

all: $(TARGET).pdf

$(TARGET).pdf: $(TARGET).ps 
	ps2pdf  $(TARGET).ps $(TARGET).pdf

$(TARGET).ps: $(TARGET).dvi $(wildcard *.eps)
	dvips  $(TARGET).dvi -o $(TARGET).ps

$(TARGET).dvi: $(TARGET).tex 
	latex $(TARGET).tex 

clean: 
	rm -f *~ *bak $(TARGET).{vrb,snm,out,nav,toc,aux,ps,log,lof,bbl,blg,dvi,pdf} #sample_color.{vrb,snm,out,nav,toc,aux,ps,log,lof,bbl,blg,dvi,pdf} 

.PHONY: clean
