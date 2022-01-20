CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SRCS_ROOT = srcs
PARSER_ROOT = $(SRCS_ROOT)/parser
UTILS_ROOT = $(SRCS_ROOT)/utils
SHELL_ROOT = $(SRCS_ROOT)/shell
EXECUTOR_ROOT = $(SRCS_ROOT)/executor

INCLUDE_ROOT = includes

PARSER_SRCS := exp_types.c expand_filename.c expander.c expander_helper.c \
			expander_split.c lexer.c parser.c parser_command.c \
			parser_container.c parser_helper.c parser_logical_oper.c \
			parser_pipeline.c parser_redir.c tk_types_complex.c \
			tk_types_escape.c tk_types_operator.c token_container.c \
			tokenizer.c tokenizer_helper.c tokenizer_normal.c tokenizer_pair.c \
			whildcard_container.c wildcard.c wildcard_helper.c
PARSER_SRCS := $(addprefix $(PARSER_ROOT)/, $(PARSER_SRCS))

EXECUTOR_SRCS := executor.c
EXECUTOR_SRCS := $(addprefix $(EXECUTOR_ROOT)/, $(EXECUTOR_SRCS))

UTILS_SRCS := find_last_slash.c move_string.c replace_str.c streq.c
UTILS_SRCS := $(addprefix $(UTILS_ROOT)/, $(UTILS_SRCS))

SHELL_SRCS := shell.c
SHELL_SRCS := $(addprefix $(SHELL_ROOT)/, $(SHELL_SRCS))

MAIN_SRCS := minishell.c
MAIN_SRCS := $(addprefix $(SRCS_ROOT)/, $(MAIN_SRCS))

SRCS = $(PARSER_SRCS) $(MAIN_SRCS) $(SHELL_SRCS) $(UTILS_SRCS) $(EXECUTOR_SRCS)
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
	@$(MAKE) -C $(LIBRL_ROOT) install-static

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