CC =gcc -Wall -Wextra -Werror
CLEAN =rm -f
NAME_PROGRAM =pong
SOURCE =main.c


all: $(NAME_PROGRAM)


rebuild: clean all


clean:
	$(CLEAN) $(NAME_PROGRAM)


$(NAME_PROGRAM): $(SOURCE)
	$(CC) $^ -o $@
