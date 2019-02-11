##
## Makefile for PSU_2016_myftp in /home/kevin/rendu/PSU_2016_myftp
## 
## Made by kevin
## Login   <kevin3.nguyen@epitech.eu>
## 
## Started on  Tue May  9 14:18:40 2017 kevin
## Last update Sun May 21 23:17:56 2017 kevin
##

RM      = rm -f

NAME    = server

CFLAGS += -Wall -Wextra -Werror
CFLAGS += -I./include

SRC	= src/cmd_connected.c \
	  src/cmd_connection.c \
	  src/serveur.c \
	  src/tools.c \
	  src/tools_file.c \
	  src/cmd_pasv.c \
	  src/cmd_connected2.c \
	  src/cmd_stor.c


OBJ    = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME) -L./lib 

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
