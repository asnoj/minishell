# **************************************************************************** #
#                                MINISHELL                                     #
# **************************************************************************** #
NAME        = minishell

# Compiler
CC          = cc
CFLAGS      = -g3 -g
RM          = rm -rf

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = include
LIBFT_DIR   = libft

# Libft
LIBFT       = $(LIBFT_DIR)/libft.a

# Readline
READLINE    = -lreadline

# Source files
SRC_FILES   = main_utils/main.c \
              main_utils/main_utils1.c \
              main_utils/main_utils2.c \
              main_utils/exit_utils_2.c \
              main_utils/verif_cmd.c \
              main_utils/verif_cmd_2.c \
              main_utils/verif_cmd_3.c \
              main_utils/exit.c \
              main_utils/exit_utils.c \
              parsing/tokenizer.c \
              parsing/tokenizer_utils.c \
              parsing/tokenizer_utils2.c \
              parsing/tokenizer_utils3.c \
              parsing/tokenizer_utils4.c \
              parsing/token_cmd.c \
              parsing/token_cmd_utils.c \
              parsing/token_cmd2.c \
              parsing/token_cmd2_2.c \
              parsing/token_cmd_3.c \
              parsing/free_one_redirect.c \
			  parsing/expand.c \
			  parsing/expand_utils.c \
              parsing/syntax.c \
              parsing/fill_all_tokens.c \
              execution/child.c \
              execution/child2.c \
              execution/choose_cmd_2.c \
              execution/from_pipex.c \
              execution/choose_cmd.c \
              execution/from_pipex_2.c \
              execution/from_pipex_3.c \
              builtins/fuction_for_cd.c \
              builtins/fuction_for_cd2.c \
              builtins/other_command.c \
              builtins/other_command_utils.c \
              builtins/echo.c \
              builtins/ft_unset.c \
              builtins/for_env.c \
              builtins/for_env_2.c \
              builtins/for_export.c \
              redirections/here_doc.c \
              redirections/here_doc_norm.c \
              redirections/fn_match.c \
              redirections/here_doc_utils.c \
              redirections/fn_match_utils.c \
              redirections/collect_heredoc.c \
              redirections/heredoc_expand.c \
              signals/signal.c \
              signals/signal_2.c \
              utils/utils.c \
              utils/clean_exit.c \
              utils/utils_2.c \
              utils/sturct_utils.c \
              utils/split_modif.c

SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Colors
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RED         = \033[0;31m
RESET       = \033[0m

# Rules
all:        $(NAME)

$(NAME):    $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)
	@echo "$(GREEN)✔ $(NAME) compiled successfully!$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_DIR) bonus --silent

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --silent
	@echo "$(YELLOW)✔ Object files removed.$(RESET)"

fclean:     clean
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean --silent
	@echo "$(RED)✔ $(NAME) removed.$(RESET)"

re:         fclean all

.PHONY:     all clean fclean re
