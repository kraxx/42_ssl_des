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
			util \
			write \
			endians \
			permutations \
			generate_keys \
			check_stdin \
			base64 \
			base64_encode \
			des_ecb \
			des_util \
			des_encode \
			des_cbc \
			des_cbc_util \
			des3_cbc

HDR =		ft_ssl_des \
			ft_des_num 

SRC_DIR =		src/
SRC_C =			$(addsuffix .c, $(SRC))
SRC_FILES =		$(addprefix $(SRC_DIR), $(SRC_C))

OBJ_DIR =		obj/
OBJ_O =			$(addsuffix .o, $(SRC))
OBJ_FILES =		$(addprefix $(OBJ_DIR), $(OBJ_O))

LIBFT_DIR =		libft/
LIBFT_A =		libft.a
LIBFT_FILES =	$(addprefix $(LIBFT_DIR), $(LIBFT_A))

LIBFT_HDR_DIR =	libft/includes/

HDR_DIR =		includes/
HDR_H =			$(addsuffix .h, $(HDR))
HDR_FILES =		$(addprefix $(HDR_DIR), $(HDR_H))

C_FLAGS =		-Wall -Wextra -Werror
OPT_FLAGS = 	-O3

RED =				\033[31m
GREEN =				\033[32m
BLUE =				\033[34m
YELLOW =			\033[33m
MAGENTA =			\033[35m
GREY =				\033[37m
GREEN_LIGHT =		\033[92m
YELLOW_LIGHT =		\033[93m
YELLOW_BOLD =		\033[1;33m
YELLOW_LIGHT_BOLD =	\033[1;93m
MAGENTA_LIGHT =		\033[95m
BLINK =				\033[5m
GREEN_LIGHT_BLINK =	\033[5;92m
END_COLOUR =		\033[0m

.SILENT:

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT_FILES)
	@echo "$(YELLOW_LIGHT)$(NAME): $(YELLOW)Compiling $(NAME)...$(END_COLOUR)"
	@gcc $(C_FLAGS) $(OPT_FLAGS) $^ -o $@
	@echo "$(YELLOW_LIGHT)$(NAME): $(GREEN)Successfully compiled $(NAME)!$(END_COLOUR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDR_FILES)
	@mkdir -p obj
	@gcc $(C_FLAGS) -I $(HDR_DIR) -I $(LIBFT_HDR_DIR) -c $< -o $@

$(LIBFT_FILES): force
	@make -C $(LIBFT_DIR)

force:
	@true

clean:
	@echo "$(YELLOW_LIGHT)$(NAME): $(YELLOW)Cleaning objects...$(END_COLOUR)"
	@/bin/rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "$(YELLOW_LIGHT)$(NAME): $(GREEN)Successfully cleaned all objects!$(END_COLOUR)"

fclean: clean
	@echo "$(YELLOW_LIGHT)$(NAME): $(YELLOW)Cleaning executable...$(END_COLOUR)"
	@/bin/rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(YELLOW_LIGHT)$(NAME): $(GREEN)Successfully cleaned everything!$(END_COLOUR)"

re:	fclean all

.PHONY: all force clean fclean re
