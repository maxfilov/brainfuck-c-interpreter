TARGET_DIR=target/
OBJ_DIR=${TARGET_DIR}obj/
TEST_DIRECTORY=${TARGET_DIR}tests/
EXECUTABLE=${TARGET_DIR}brainfuck
CC=gcc
CFLAGS=-Wall -Wextra
build: directory interpreter.o stack.o io.o brainfuck.o
	@${CC} ${CFLAGS} -O3 ${OBJ_DIR}interpreter.o ${OBJ_DIR}stack.o ${OBJ_DIR}brainfuck.o ${OBJ_DIR}io.o -o ${EXECUTABLE}
	@echo "Linked"

directory:
	@mkdir -p ${OBJ_DIR}
	@echo "Created output directory"

%.o: %.c
	@${CC} ${CFLAGS}  -c "src/$<" -o "${OBJ_DIR}$@"

%.c:
	@echo "Compiling $@"

test: create_test_directory lera.bf maksim.bf hello_world.bf
	@echo "Finished testing"

create_test_directory:
	@mkdir -p ${TEST_DIRECTORY}

%.bf:
	@echo "Testing test/$@.input"
	@${EXECUTABLE} < test/$@.input > ${TEST_DIRECTORY}/$@.output
	@diff ${TEST_DIRECTORY}/$@.output test/$@.output

clean:
	@rm -rf ${TARGET_DIR}
	@echo "Cleaned directory"
