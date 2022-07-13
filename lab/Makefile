LATEX := xelatex
IMGDIR := ../_img

main.pdf: main.tex fs.tex io.tex ipc.tex locking.tex mm.tex proc.tex sched.tex
	-$(LATEX) $<
	-$(LATEX) $<

clean:
	$(RM) main.aux main.log main.out main.pdf main.toc
