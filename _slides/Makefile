LATEX := xelatex
IMGDIR := ../_img

main.pdf: main.tex intro.tex proc.tex thread.tex \
		ipc.tex sync.tex deadlock.tex\
		mem.tex address-space.tex vmem.tex\
		io.tex $(IMGDIR)/hard-disk.tex \
		fs.tex vfs.tex ext4.tex  \
		$(IMGDIR)/vfs.tex $(IMGDIR)/vfs-sys.tex
	$(LATEX) $< && $(LATEX) $<

clean:
	$(RM) main.aux main.log main.nav\
		main.out main.pdf main.snm\
		main.toc
