OBJ   = obj/main.o      \
		obj/hamlet.o    \
		obj/errors.o    \
		obj/general.o   \
		obj/my_sort.o

FLAGS = -lubsan -D NDEBUG -g -std=c++14 -fmax-errors=1 			  	\
		-Wc++0x-compat -Wc++11-compat -Wc++14-compat  				\
		-Wcast-qual -Wchar-subscripts -Wconditionally-supported 	\
		-Wconversion  -Wctor-dtor-privacy -Wempty-body 				\
		-Wfloat-equal -Wformat-nonliteral -Wformat-security 		\
		-Wformat-signedness -Wformat=2 -Winline  -Wlogical-op 		\
		-Wmissing-declarations  -Wnon-virtual-dtor -Wopenmp-simd	\
		-Woverloaded-virtual -Wpacked -Wpointer-arith 				\
		-Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo	\
		-Wstack-usage=8192  -Wstrict-null-sentinel 					\
		-Wstrict-overflow=2 -Wsuggest-attribute=noreturn 			\
		-Wsuggest-final-methods -Wsuggest-final-types  				\
		-Wsuggest-override -Wswitch-default -Wswitch-enum 			\
		-Wsync-nand -Wundef  -Wunreachable-code -Wunused 			\
		-Wuseless-cast -Wvariadic-macros -Wno-literal-suffix 		\
		-Wno-missing-field-initializers -Wno-narrowing				\
		-Wno-old-style-cast -Wno-varargs -fcheck-new 				\
		-fsized-deallocation  -fstack-protector 					\
		-fstrict-overflow   -flto-odr-type-merging 					\
		-fno-omit-frame-pointer -fPIE -fsanitize=address  			\
		-fsanitize=bool -fsanitize=bounds -fsanitize=enum  			\
		-fsanitize=float-cast-overflow 								\
		-fsanitize=float-divide-by-zero 							\
		-fsanitize=integer-divide-by-zero -fsanitize=leak 			\
		-fsanitize=nonnull-attribute -fsanitize=null 				\
		-fsanitize=object-size -fsanitize=return 					\
		-fsanitize=returns-nonnull-attribute -fsanitize=shift 		\
		-fsanitize=signed-integer-overflow -fsanitize=undefined 	\
		-fsanitize=unreachable -fsanitize=vla-bound 				\

all: global

global: $(OBJ)
	g++ $(OBJ) -o sort -lm $(FLAGS)

obj/main.o: main.cpp hamlet/hamlet.h general/general.h errors/errors.h
	g++ main.cpp -c -o obj/main.o $(FLAGS)

obj/hamlet.o: hamlet/hamlet.cpp hamlet/hamlet.h errors/errors.h
	g++ hamlet/hamlet.cpp -c -o obj/hamlet.o $(FLAGS)

obj/errors.o: errors/errors.cpp errors/errors.h general/general.h
	g++ errors/errors.cpp -c -o obj/errors.o $(FLAGS)

obj/general.o: general/general.cpp general/general.h
	g++ general/general.cpp -c -o obj/general.o $(FLAGS)

obj/my_sort.o: my_sort/my_sort.cpp my_sort/my_sort.h hamlet/hamlet.h
	g++ my_sort/my_sort.cpp -c -o obj/my_sort.o $(FLAGS)
.PHONY: cleanup

cleanup:
	rm obj/*.o sort