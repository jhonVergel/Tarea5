
imagenes: plots.py datos.dat 
	python plots.py 
	pdflatex Resultados_hw5.tex
datos.dat:Curva
	./Curva.x> datos.dat
Curva: CurvaRotacion.c
	gcc CurvaRotacion.c -lm -o Curva.x
	


	

	
	
