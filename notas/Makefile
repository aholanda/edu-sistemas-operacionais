TEXES := 01-proc.tex  02-ipc.tex  03-mem.tex  04-io-storage.tex

main.pdf: main.tex $(TEXES)
	-xelatex $< && xelatex $<

.PHONY: clean
clean:
	$(RM) *.aux *.log *.out main.pdf
