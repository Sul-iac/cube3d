NAME    := cub3D
CC      := cc
CFLAGS  := -Iincludes
SRCDIR  := src
INCDIR  := includes
MLXDIR  := minilibx-linux

SRCS    := $(wildcard $(SRCDIR)/*.c)
OBJS    := $(SRCS:.c=.o)

MLX     := $(MLXDIR)/libmlx_Linux.a
LIBS    := -L$(MLXDIR) -lmlx_Linux -lXext -lX11 -lm

GREEN   := \033[0;32m
RESET   := \033[0m

all: $(NAME)

$(NAME): $(MLX) $(OBJS)
	@printf "$(GREEN)[Link]\t$@$(RESET)\n"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

$(MLX):
	@$(MAKE) -C $(MLXDIR)

%.o: %.c
	@printf "$(GREEN)[Comp]\t$<$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(MLXDIR) clean
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
