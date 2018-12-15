.PHONY: all clean fclean re

NAME		:=	server

SRC_D		:=	src/
SRC_DI		:=	includes/
SHARED_P	:=	../generalDir/
SHARED_D	:=	$(SHARED_P)src/
SHARED_DI	:=	$(SHARED_P)includes/
OBJ_D		:=	.obj/

CC			:=	clang
CFLAGS		:=	-Wall -Wextra -Werror --std=c99
IFLAGS		:=	-I $(SRC_DI)serverCS.h -I $(SHARED_DI)generalCS.h
SRC_F		:=	server compress requestsFunctions
SHARED_F	:=	handleSignals handleErrors secondaryFunctions

HDRS		:=	$(wildcard $(SRC_DI)*.h) $(wildcard $(SHARED_DI)*.h)
SRCS		:=	$(addprefix $(SRC_D), $(addsuffix .c, $(SRC_F)))
SRCS		+=	$(addprefix $(SHARED_D), $(addsuffix .c, $(SHARED_F)))
OBJS		:=	$(addprefix $(OBJ_D), $(SRCS:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ_D) $(OBJS)
	$(CC) $(IFLAGS) $(CFLAGS) $(wildcard $(OBJ_D)$(SRC_D)*.o) -o $(NAME)
	@ echo "server: done"
$(OBJ_D):
	mkdir -p $(OBJ_D)$(SRC_D)
$(OBJ_D)%.o: %.c $(HDRS)
	$(CC) $(IFLAGS) $(CFLAGS) -o $(shell echo "$@" | sed -e "s|$(SHARED_P)||g") -c $<

clean:
	@ rm -rf $(OBJ_D)
	@ echo "server: objects removed"
fclean: clean
	@ rm -f $(NAME) 
	@ echo "server: binary removed"
re: fclean all
