CC=c++
name = Bureaucrat
flgas = -Wall -Wextra -Werror
flag = -std=c++98
SRC = main.cpp Bureaucrat.cpp
OBG = $(SRC:.cpp=.o)

all : $(name)

$(name) : $(OBG)
	$(CC) $(flgas) $(flag) $(OBG) -o $(name)
%.o : %.cpp
	$(CC) $(FLAGS) $(flag) -c $< -o $@

clean :
	rm -f $(name) $(OBG)
fclean : clean
	rm -f $(name)
re: fclean all

.PHONY : all fclean clean re