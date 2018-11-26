
report.pdf:
	pandoc --filter pandoc-citeproc --bibliography=references.bib --variable papersize=a4paper -V geometry:margin=1.0in -V fontsize=12pt --toc -Vlof -Vlot  -s report.md -o report.pdf

slides:
	pandoc -t revealjs -s presentation.md -o slides.html --slide-level=2 --mathml

slides.pdf:
	pandoc -t beamer -s presentation.md -o slides.pdf --slide-level=2 --mathml
