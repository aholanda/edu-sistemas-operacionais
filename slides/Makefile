LATEX := xelatex

texs := $(wildcard *.tex)
imgs := $(wildcard *.png)

main.pdf: main.tex $(texs) $(png)
	@$(LATEX) $< && $(LATEX) $<

slides: main.pdf

clean:
	$(RM) *.aux *.log *.nav *.out main.pdf *.snm *.toc *.xdv
