archive.pdf : archive.tex
	pdflatex -shell-escape archive

test:
	cd testing; find ../code -name "*.cpp" -exec ./trycompile.sh "{}" \;
