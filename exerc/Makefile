main.pdf: main.tex deadlock.tex\
		mm.tex\
	  	io.tex fs.tex
	xelatex $<

.PHONY: clean
clean:
	$(RM) *.aux *.log *.out main.pdf
