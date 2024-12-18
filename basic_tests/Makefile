CC = cc
CFLAGS = -Wall -Wextra -Werror

# Explicitly define source directories
MANDATORY_SOURCES = mandatory_tests.c ../get_next_line.c ../get_next_line_utils.c
BONUS_SOURCES = bonus_tests.c ../get_next_line_bonus.c ../get_next_line_utils_bonus.c

MANDATORY_EXEC = mandatory_tests
BONUS_EXEC = bonus_tests

# Targets
all: m

m: $(MANDATORY_EXEC)

$(MANDATORY_EXEC): $(MANDATORY_SOURCES)
	$(CC) $(CFLAGS) $(MANDATORY_SOURCES) -o $(MANDATORY_EXEC)

bonus: $(BONUS_EXEC)

$(BONUS_EXEC): $(BONUS_SOURCES)
	$(CC) $(CFLAGS) $(BONUS_SOURCES) -o $(BONUS_EXEC)

# Clean up object files and executables
clean:
	rm -f $(MANDATORY_EXEC) $(BONUS_EXEC)

# Full clean (including executables)
fclean: clean

# Rebuild everything
re: fclean all

# Mark these as not actual files, just targets
.PHONY: all m bonus clean fclean re
