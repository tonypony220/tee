SRCS	=   main.cpp
OBJS	=	${SRCS:.cpp=.o}
CFLAGS	=   -Wall -Wextra -Werror --std=c++98 # -fsanitize=address
CC		=	clang++
RM		=	-rm	-f
HEAD	=	tee.hpp
NAME	=	te

%.o: %.cpp $(HEAD)
	$(CC) ${CFLAGS} -c $< -o ${<:.cpp=.o}

${NAME}: ${OBJS}
		$(CC) ${CFLAGS} ${OBJS} -o ${NAME}

all: ${NAME}

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:		fclean all

.PHONY:	all bonus clean fclean re
