LIB_PATHS = -L/usr/X11R6/lib -L/usr/lib
LIBS = -lglut -lGLU -lGL -lm -L/usr/X11/lib -lXext -lX11 

CC = g++

EXEC = env_conv
NAME = Projet_maths

all: main.cpp point.o filedatamanager.o calculEnveloppeConvexe.o graphique.o programme.o openglmanager.o callbacks.o
	$(CC) $^ -o $(EXEC) $(LIB_PATHS) $(LIBS)

%.o: %.c %.h
	$(CC) -c $< -o $@
	
execute: all
	./$(EXEC) $(FILE)
	
clean:
	rm -rf *.o

empty: clean
	rm -rf $(EXEC) $(NAME)*.t* *.out
	
archive: empty
	tar -cvf $(NAME).tar ../$(NAME)
	
compress: archive
	gzip $(NAME).tar
	mv $(NAME).tar.gz $(NAME).tgz
	
content: 
	tar -tf $(NAME)*.t*
	
.PHONY: all main execute clean empty archive compress
