# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsalmi <lsalmi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/02 13:36:06 by lsalmi            #+#    #+#              #
#    Updated: 2023/08/02 13:36:11 by lsalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = main.c routine.c utils.c init.c monitor.c threads.c eating.c
OBJS = $(SRCS:.c=.o)

INCL = -I./philo.h
FLAGS = -Wall -Wextra -Werror -fsanitize=address

all: $(NAME) $(OBJS)

## @ = target, @D target dir, < = first dependency, ^ = all deps
$(NAME): $(OBJS)
	@cc -fsanitize=address -o $(@) $(^)
	@echo "Executable $(@) created"

%.o: %.c
	@cc -c $(FLAGS) $(INCL) $(<) -o $(@)

clean:
	@rm -f $(OBJS)
	@echo "Object files deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) deleted"

re: fclean all

.PHONY: all clean fclean re
