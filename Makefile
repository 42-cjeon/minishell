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

PARSER_SRCS := exp_types.c expand_filename.c expander.c expander_helper.c \
			expander_split.c lexer.c parser.c parser_command.c \
			parser_container.c parser_helper.c parser_logical_oper.c \
			parser_pipeline.c parser_redir.c tk_types_complex.c \
			tk_types_escape.c tk_types_operator.c token_container.c \
			tokenizer.c tokenizer_helper.c tokenizer_normal.c tokenizer_pair.c \
			wildcard_container.c wildcard.c wildcard_helper.c parser_clear.c \
			parser_cmd_clear.c
PARSER_SRCS := $(addprefix $(PARSER_ROOT)/, $(PARSER_SRCS))

EXECUTOR_SRCS := executor.c
EXECUTOR_SRCS := $(addprefix $(EXECUTOR_ROOT)/, $(EXECUTOR_SRCS))

UTILS_SRCS := find_last_slash.c move_string.c replace_str.c streq.c
UTILS_SRCS := $(addprefix $(UTILS_ROOT)/, $(UTILS_SRCS))

SHELL_SRCS := shell.c shell_print.c
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

# -- 나중에 지우기 -- #
TEST_SRCS := minishell.c
TEST_SRCS := $(addprefix $(SRCS_ROOT)/test/, $(TEST_SRCS))
TSRCS = $(PARSER_SRCS) $(TEST_SRCS) $(UTILS_SRCS)
TOBJS = $(TSRCS:.c=.o)
# --            -- #

LIBFT_ROOT = $(SRCS_ROOT)/libft
LIBFT = $(LIBFT_ROOT)/libft.a

LIBRL_ROOT = $(SRCS_ROOT)/readline
LIBRL_INCLUDE_ROOT = $(SRCS_ROOT)
LIBRL = $(LIBRL_ROOT)/libreadline.a
LIBRL_HISTORY = $(LIBRL_ROOT)/libhistory.a

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(LIBRL) $(LIBRL_HISTORY)
	$(CC) $(CFLAGS) -lncurses -o $@ $^

%.o : %.c
	$(CC) -I$(INCLUDE_ROOT) -I$(LIBRL_INCLUDE_ROOT) -c $(CFLAGS) -o $@ $<

$(LIBFT) :
	@$(MAKE) -C $(LIBFT_ROOT) INCLUDE_ROOT=$(realpath $(INCLUDE_ROOT)) all

$(LIBRL) :
	@$(MAKE) -C $(LIBRL_ROOT) all

# -- 나중에 지우기 -- #
test : $(TOBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^
# --            -- #

clean :
	@$(MAKE) -C $(LIBFT_ROOT) clean
	@$(MAKE) -C $(LIBRL_ROOT) clean
	rm -f $(OBJS)
# -- 나중에 지우기 -- #
	rm -f $(TOBJS)
	rm -f test
# --           -- #

fclean : clean
	@$(MAKE) -C $(LIBFT_ROOT) fclean
	@$(MAKE) -C $(LIBRL_ROOT) clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re