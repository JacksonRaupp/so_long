# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jraupp <jraupp@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 17:45:17 by jraupp            #+#    #+#              #
#    Updated: 2023/12/14 14:23:31 by jraupp           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	so_long
CFLAGS	:=	-Wextra -Wall -Werror -Wunreachable-code -g -Ofast
LIBMLX	:=	./library/MLX42
LEAKS = valgrind --leak-check=full --show-leak-kinds=all --gen-suppressions=all --suppressions=../so_long/suppress.sup

HEADERS	:=	-I ./include -I $(LIBMLX)/include
LIBS	:=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
FILE	:=	so_long			\
			utils			\
			ft_printf		\
			ft_printf_str	\
			ft_printf_nbr	\
			step_1			\
			step_2			\
			step_3			\
			step_4			\
			step_5			\
			step_6			\
			step_7			\

SRCS	:=	$(addprefix source/, $(addsuffix .c, $(FILE)))
OBJS	:=	$(addprefix objects/, $(addsuffix .o, $(FILE)))

all: $(NAME)

objects/%.o: source/%.c | objects
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

objects:
	@mkdir -p objects

play:
	$(LEAKS) ./so_long ./map/map.ber

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME) objects

re: fclean all

.PHONY: all clean fclean re
