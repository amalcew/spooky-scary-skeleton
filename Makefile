LIBS=-lGL -lglfw -lGLEW -lassimp
HEADERS=constants.h mesh.h meshmodel.h meshmodelskeleton.h MeshModelSpeaker.h MeshModelSkeletonSpin.h MeshModelSkeletonHeadbang.h lodepng.h shaderprogram.h custom_camera.h
FILES=meshmodel.cpp mesh.cpp meshmodelskeleton.cpp MeshModelSpeaker.cpp MeshModelSkeletonSpin.cpp MeshModelSkeletonHeadbang.cpp lodepng.cpp  main_file.cpp  shaderprogram.cpp custom_camera.cpp

main_file: $(FILES) $(HEADERS)
	g++ -o main_file $(FILES)  $(LIBS) -I.
