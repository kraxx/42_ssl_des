# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/21 22:34:31 by jchow             #+#    #+#              #
#    Updated: 2017/06/21 22:34:32 by jchow            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		ft_ssl

SRC = 		main \
			error \
			endians \
			permutations \
			generate_keys \
			check_stdin \
			util \
			base64 \
			base64_encode \
			des_ecb \
			des_encode \
			des_cbc \

HDR =		ft_ssl_des \
			ft_des_num

SRC_DIR = 	src/
SRC_FILES =	$(addsuffix .c, $(SRC))
SRCS =		$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR =	obj/
OBJ_FILES =	$(addsuffix .o, $(SRC))
OBJS =		$(addprefix $(OBJ_DIR), $(OBJ_FILES))

LFT_DIR =	libft/
LFT_FILES =	libft.a
LFTS =		$(addprefix $(LFT_DIR), $(LFT_FILES))

HDR_DIR =	-I includes -I libft/includes
HDR_FILES =	includes/ft_ssl_des.h includes/ft_des_num.h
# HDR_FILES = includes/$(addsuffix .h, $(HDR))

C_FLAGS =	-Wall -Wextra -Werror

RED =				[31m
GREEN =				[32m
BLUE =				[34m
YELLOW =			[33m
MAGENTA =			[35m
GREY =				[37m
GREEN_LIGHT =		[92m
YELLOW_LIGHT =		[93m
YELLOW_BOLD =		[1;33m
YELLOW_LIGHT_BOLD =	[1;93m
MAGENTA_LIGHT =		[95m
BLINK =				[5m
GREEN_LIGHT_BLINK =	[5;92m
END_COLOUR =		\033[0m

.SILENT:

all: $(NAME)

$(NAME): $(OBJS) $(LFTS)
	@echo "$(YELLOW)Compiling $(NAME)...$(END_COLOUR)"
	@gcc $(C_FLAGS) $^ -o $@
	@echo "$(GREEN)Successfully compiled $(NAME)!$(END_COLOUR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDR_FILES)
	@mkdir -p obj
	@gcc $(C_FLAGS) $(HDR_DIR) -c $< -o $@

$(LFTS): force
	@make -C $(LFT_DIR)

force:
	@true

clean:
	@echo "$(YELLOW)Cleaning objects...$(END_COLOUR)"
	@/bin/rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)Cleaning library objects...$(END_COLOUR)"
	@make clean -C $(LFT_DIR)
	@echo "$(GREEN)Successfully cleaned all objects!$(END_COLOUR)"

fclean: clean
	@echo "$(YELLOW)Cleaning executable...$(END_COLOUR)"
	@/bin/rm -f $(NAME)
	@echo "$(YELLOW)Cleaning libraries...$(END_COLOUR)"
	@make fclean -C $(LFT_DIR)
	@echo "$(GREEN)Successfully cleaned everything!$(END_COLOUR)"

re:	fclean all

.PHONY: all force clean fclean re