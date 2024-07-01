#!/bin/sh

pdflatex man_back.tex
pdflatex man_front.tex

rm man_back.aux man_back.log man_front.aux man_front.log 
