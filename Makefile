CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SRCS_ROOT = srcs
PARSER_ROOT = $(SRCS_ROOT)/parser
EXECUTOR_ROOT = $(SRCS_ROOT)/executor
UTILS_ROOT = $(SRCS_ROOT)/utils
SHELL_ROOT = $(SRCS_ROOT)/shell
ENVS_ROOT = $(SRCS_ROOT)/envs
BUILTIN_ROOT = $(SRCS_ROOT)/builtin

INCLUDE_ROOT = includes

READLINE_ROOT = $(shell brew --prefix readline)
READLINE_INCLUDE = $(READLINE_ROOT)/include
READLINE_LIB = $(READLINE_ROOT)/lib

PARSER_SRCS := exp_types.c expand_filename.c expander.c expander_helper.c \
			expander_split.c lexer.c parser.c parser_command.c \
			parser_container.c parser_helper.c parser_logical_oper.c \
			parser_pipeline.c parser_redir.c tk_types_complex.c \
			tk_types_escape.c tk_types_operator.c token_container.c \
			tokenizer.c tokenizer_helper.c tokenizer_normal.c tokenizer_pair.c \
			wildcard_container.c wildcard.c wildcard_helper.c parser_clear.c \
			parser_cmd_clear.c expander_variable.c
PARSER_SRCS := $(addprefix $(PARSER_ROOT)/, $(PARSER_SRCS))

EXECUTOR_SRCS := execute_command.c execute_helper.c executor.c pipe_helper.c \
				redirection.c redirection_heredoc.c stdio_helper.c wait_child.c
EXECUTOR_SRCS := $(addprefix $(EXECUTOR_ROOT)/, $(EXECUTOR_SRCS))

UTILS_SRCS := find_last_slash.c move_string.c replace_str.c streq.c
UTILS_SRCS := $(addprefix $(UTILS_ROOT)/, $(UTILS_SRCS))

SHELL_SRCS := shell.c shell_print.c shell_readline.c
SHELL_SRCS := $(addprefix $(SHELL_ROOT)/, $(SHELL_SRCS))

ENVS_SRCS := cenv.c cenv_print.c envs.c envs_func.c
ENVS_SRCS := $(addprefix $(ENVS_ROOT)/, $(ENVS_SRCS))

BUILTIN_SRCS := ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c
BUILTIN_SRCS := $(addprefix $(BUILTIN_ROOT)/, $(BUILTIN_SRCS))

MAIN_SRCS := minishell.c
MAIN_SRCS := $(addprefix $(SRCS_ROOT)/, $(MAIN_SRCS))

SRCS = $(PARSER_SRCS) $(MAIN_SRCS) $(SHELL_SRCS) $(UTILS_SRCS) \
			$(EXECUTOR_SRCS) $(ENVS_SRCS) $(BUILTIN_SRCS)
OBJS = $(SRCS:.c=.o)

LIBFT_ROOT = $(SRCS_ROOT)/libft
LIBFT = $(LIBFT_ROOT)/libft.a

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -L$(READLINE_LIB) -lreadline -lhistory -lncurses -o $@ $^

%.o : %.c
	$(CC) -I$(READLINE_INCLUDE) -I$(INCLUDE_ROOT) -c $(CFLAGS) -o $@ $<

$(LIBFT) :
	@$(MAKE) -C $(LIBFT_ROOT) INCLUDE_ROOT=$(realpath $(INCLUDE_ROOT)) all

clean :
	@$(MAKE) -C $(LIBFT_ROOT) clean
	rm -f $(OBJS)

fclean : clean
	@$(MAKE) -C $(LIBFT_ROOT) fclean
	rm -f $(NAME)

re : fclean all

norm :
	@echo "[-] check srcs"
	@norminette $(SRCS)
	@echo "[-] check includes"
	@norminette $(INCLUDE_ROOT)

.PHONY : all clean fclean re norm
