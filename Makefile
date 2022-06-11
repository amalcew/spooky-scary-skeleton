LIBS=-lGL -lglfw -lGLEW -lassimp
HEADERS=meshmodel.h constants.h lodepng.h shaderprogram.h
FILES=meshmodel.cpp lodepng.cpp  main_file.cpp  shaderprogram.cpp

main_file: $(FILES) $(HEADERS)
	g++ -o main_file $(FILES)  $(LIBS) -I.
