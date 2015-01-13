# "make madlab" Build the madlab.o output 
madlab:
	gcc madlab.c -c -g -std=c99 -pedantic -Wall -Werror 

# "make exe" Build the executable from separate madlab and interpreter outputs
exe:
	gcc madlab.o interpreter.o -o madlabR -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm

# "make basic"
basic:
	gcc madlab.c -o madlabR -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm

# "make interpreter"
interpreter:
	gcc interpreter.c -c -g -std=c99 -pedantic -Wall -Werror

# "make clean" Remove the last built executable
clean:
	rm madlabR