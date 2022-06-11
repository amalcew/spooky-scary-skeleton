LIBS=-lGL -lglfw -lGLEW -lassimp
HEADERS=constants.h meshmodel.h lodepng.h shaderprogram.h custom_camera.h
FILES=meshmodel.cpp lodepng.cpp  main_file.cpp  shaderprogram.cpp custom_camera.cpp

main_file: $(FILES) $(HEADERS)
	g++ -o main_file $(FILES)  $(LIBS) -I.
