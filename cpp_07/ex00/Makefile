<<<<<<< HEAD
NAME = Identify
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS= main.cpp
OBJS=$(SRCS:.cpp=.o)

all:$(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean :
	@rm -f $(OBJS)
fclean : clean
	@rm -f $(NAME)
re : fclean all
=======
NAME = array_test
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
all: $(NAME)
$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
>>>>>>> 1f99390516a3159bcdd63437145e8ef7708ac85f
