archive.pdf : archive.tex
	pdflatex -shell-escape archive
	rm ../latest.pdf
	ln -s -r archive.pdf ../latest.pdf

test:
	cd testing; find ../code -name "*.cpp" -exec ./trycompile.sh "{}" \;

format:
	clang-format -style=file -i code/*/*.cpp
