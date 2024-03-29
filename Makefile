NAME = pipex

FLAGS = -Wall -Werror -Wextra -g

LIBFT_DIR = ./libs/libft
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

LIBFT = $(LIBFT_DIR)/libft.a

SRC = 	$(SRC_DIR)/pipex.c \
        $(SRC_DIR)/pipex_utils.c

OBJ = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC:.c=.o))

INC = -I $(INC_DIR)

COM_COLOR   = \033[0;33m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m
PRG_COLOR	= \033[0;35m
LIB_COLOR	= \033[0;34m

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@gcc $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME) 2> $@.log; \
        RESULT=$$?; \
        if [ $$RESULT -ne 0 ]; then \
            printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(PRG_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"; \
        elif [ -s $@.log ]; then \
            printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(PRG_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"; \
        else  \
            printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(PRG_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
        fi; \
        cat $@.log; \
        rm -f $@.log; \
        exit $$RESULT
	

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@gcc $(FLAGS) $(INC) -c -o $@ $< 2> $@.log; \
        RESULT=$$?; \
        if [ $$RESULT -ne 0 ]; then \
            printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"; \
        elif [ -s $@.log ]; then \
            printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"; \
        else  \
            printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
        fi; \
        cat $@.log; \
        rm -f $@.log; \
        exit $$RESULT

$(LIBFT):
	@printf "$(COM_COLOR)$(COM_STRING) $(LIB_COLOR)$(@)$(NO_COLOR)\n";
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@printf "%b" "$(COM_COLOR)Cleaning $(LIB_COLOR)libft\n"
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@printf "%b" "$(ERROR_COLOR)Removing $(OBJ_COLOR)object files\n"
	@rm -rf $(OBJ_DIR)

fclean:	clean
	@printf "%b" "$(ERROR_COLOR)Removing $(PRG_COLOR)push_swap\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re