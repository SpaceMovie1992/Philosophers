NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

BINDIR = bin

SRCS = error_and_msg.c time_and_sleep.c utils.c main.c

OBJS = $(SRCS:.c=$(BINDIR)/%.o)

all: $(NAME)

.SILENT:

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(LIBFT) -o $(NAME) $(OBJS)
		echo $(GREEN)"Building $(NAME)"$(DEFAULT);

$(BINDIR):
		mkdir -p $@

$(BINDIR)/%.o: %.c | $(BINDIR)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		@rm -f $(OBJS)
		@rm -rf $(BINDIR)
		echo $(RED)"Removing $(NAME) object files"$(DEFAULT);

fclean: clean
		@rm -f $(NAME)
		echo $(RED)"Removing $(NAME)"$(DEFAULT);

re: fclean all
	echo $(GREEN)"Rebuilding everything"$(DEFAULT);

.PHONY: all clean fclean re

# Colors
DEFAULT = "\033[39m"
GREEN = "\033[32m"
RED = "\033[31m"
