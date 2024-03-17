SRCS		=	$(addprefix srcs/,ft_split.c execute_cmd.c main.c)

OBJS		=	${SRCS:.c=.o}

NAME		= pipex

RM		= rm -f

CC		= cc

CFLAGS		=  -Wall -Wextra -Werror -Iincludes

all:		${NAME}

${NAME}:	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:		fclean all

.PHONY:		all fclean clean re
