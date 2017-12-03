
imagenes: plots.py datos.dat 
	python plots.py 
	pdflatex Resultados_hw5.tex
datos.dat:Curva
	./Curva.x> datos.dat
Curva: CurvaRotacion.c
	sed '1d' RadialVelocities.dat > mynewfile.txt
	gcc CurvaRotacion.c -lm -o Curva.x
	


	

	
	
