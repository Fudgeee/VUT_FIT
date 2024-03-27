NAME=proj4

all: $(NAME).tex
	pdflatex $(NAME).tex
	bibtex $(NAME).aux
	pdflatex $(NAME).tex
	pdflatex $(NAME).tex

clean:
	rm -f $(NAME).aux $(NAME).dvi $(NAME).log $(NAME).c