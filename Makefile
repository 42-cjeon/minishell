CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SRCS_ROOT = srcs
PARSER_ROOT = $(SRCS_ROOT)/parser

INCLUDE_ROOT = includes

vpath %.c $(SRCS_ROOT) $(PARSER_ROOT)

PARSER_SRCS := tk_types_escape.c tk_types_operator.c \
	token_container.c tokenizer_helper.c tokenizer_normal.c \
	tokenizer_pair.c tokenize.c exp_types.c expander_helper.c \
	expander_split.c expand.c lexer.c
PARSER_SRCS := $(addprefix $(PARSER_ROOT)/, $(PARSER_SRCS))
MAIN_SRCS := minishell.c
MAIN_SRCS := $(addprefix $(SRCS_ROOT)/, $(MAIN_SRCS))

SRCS = $(PARSER_SRCS) $(MAIN_SRCS)
OBJS = $(SRCS:.c=.o)

LIBFT_ROOT = $(SRCS_ROOT)/libft
LIBFT = $(LIBFT_ROOT)/libft.a

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) -I$(INCLUDE_ROOT) -c $(CFLAGS) -o $@ $<

$(LIBFT) :
	@$(MAKE) -C $(LIBFT_ROOT) INCLUDE_ROOT=$(realpath $(INCLUDE_ROOT)) all

clean :
	@$(MAKE) -C $(LIBFT_ROOT) clean
	rm -f $(OBJS)

fclean : clean
	@$(MAKE) -C $(LIBFT_ROOT) fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re