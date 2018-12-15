.PHONY: all clean fclean re

NAME		:=	client

SRC_D		:=	src/
SRC_DI		:=	includes/
SHARED_P	:=	../generalDir/
SHARED_D	:=	$(SHARED_P)src/
SHARED_DI	:=	$(SHARED_P)includes/
OBJ_D		:=	.obj/

CC			:=	clang
CFLAGS		:=	-Wall -Wextra -Werror --std=c99
IFLAGS		:=	-I $(SRC_DI)clientCS.h -I $(SHARED_DI)generalCS.h

SRC_F		:=	client getAllLines clientFunctions
SHARED_F	:=	handleSignals handleErrors secondaryFunctions

HDRS		:=	$(wildcard $(SRC_DI)*.h) $(wildcard $(SHARED_DI)*.h)
SRCS		:=	$(addprefix $(SRC_D), $(addsuffix .c, $(SRC_F)))
SRCS		+=	$(addprefix $(SHARED_D), $(addsuffix .c, $(SHARED_F)))
OBJS		:=	$(addprefix $(OBJ_D), $(SRCS:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ_D) $(OBJS)
	$(CC) $(IFLAGS) $(CFLAGS) $(wildcard $(OBJ_D)$(SRC_D)*.o) -o $(NAME)
	@ echo "client: done"

$(OBJ_D):
	mkdir -p $(OBJ_D)$(SRC_D)
$(OBJ_D)%.o: %.c $(HDRS)
	$(CC) $(IFLAGS) $(CFLAGS) -o $(shell echo "$@" | sed -e "s|$(SHARED_P)||g") -c $<

clean:
	@ rm -rf $(OBJ_D)
	@ echo "client: objects removed"
fclean: clean
	@ rm -f $(NAME) 
	@ echo "client: binary removed"
re: fclean all
