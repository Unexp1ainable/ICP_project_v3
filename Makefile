ZIP_NAME=3-xrepka07-xnemce07
QMAKE=/home/unex/Qt/5.15.2/gcc_64/bin/qmake

default:
	$(QMAKE) -makefile -o build/Makefile && \
	cd build; make && \
	mv ICP_project_v3 ../ICP_project_v3

run: default
	./ICP_project_v3

doxygen:
	doxygen Doxyfile.txt

clean:
	rm -drf build html doc/* ICP_project_v3 $(ZIP_NAME).zip

pack:
	zip $(ZIP_NAME) -r src examples Makefile README.txt main.cpp Doxyfile.txt ICP_project_v3.pro
