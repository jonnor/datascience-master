#!/bin/bash -xe
jupyter nbconvert --to latex --template term_paper.tplx Sorting.ipynb
pdflatex Sorting
bibtex Sorting
pdflatex Sorting
pdflatex Sorting
