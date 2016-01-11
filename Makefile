include config.mak
CPPFLAGS = -std=c++11 -I./src -Wno-deprecated-register
YACC_FLAGS = --debug --verbose -d
YYLEX_FLAGS = 
J4A = ./j4a

all: j4a test

CXX_OBJS = \
	src/ast_annotation.o \
	src/ast_argument.o \
	src/ast_class.o \
	src/ast_compilation_unit.o \
	src/ast_constructor.o \
	src/ast_field.o \
	src/ast_identifier.o \
	src/ast_member.o \
	src/ast_method.o \
	src/ast_node.o \
	src/ast_property_accessor.o \
	src/ast_reference_type.o \
	src/ast__context.o \
	src/ast__namespace.o \
	src/j4a_string_pool.o \
	src/j4a_string.o \
	src/flex.j4a.yy.o \
	src/bison.j4a.tab.o \
	src/main.o \

DEPS := $(CXX_OBJS:.o=.d)
-include $(DEPS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -MM -MT $@ -MF $(patsubst %.o,%.d,$@) $<
	$(CXX) $(CPPFLAGS) -c -o $@ $<

j4a: $(CXX_OBJS)
	$(CXX) -o j4a $(CXX_OBJS)



# YACC
YACC_DEPS = \
	src/bison.j4a.y \

src/bison.j4a.tab.cpp: $(YACC_DEPS)
	$(YACC) $(YACC_FLAGS) -o $@ src/bison.j4a.y

j4acc: bison.j4a.tab.cpp
	$(CXX) -o j4acc bison.j4a.tab.cpp


# YYLEX
YYLEX_DEPS = \
	src/flex.j4a.l \
	src/bison.j4a.tab.o \

src/flex.j4a.yy.cpp: $(YYLEX_DEPS)
	$(YYLEX) $(YYLEX_FLAGS) -o $@ src/flex.j4a.l

j4alex: flex.j4a.yy.cpp
	$(CXX) -o j4alex flex.j4a.yy.cpp


# test java -> c
test/o_c/%.c: j4a

test/o_c/%.c: test/i_java/%.java
ifneq ("$<", "test/o_c/.c")
	@mkdir -p $(shell dirname $@)
	$(J4A) $< -o $@
	@diff test/ref_c/$*.c $@
	@diff test/ref_c/$*.h test/o_c/$*.h
endif

TEST_C = \
	test/o_c/java/nio/Buffer.c \
	test/o_c/java/nio/ByteBuffer.c \
	test/o_c/java/util/ArrayList.c \
	test/o_c/android/media/AudioTrack.c \
	test/o_c/android/media/MediaCodec.c \
	test/o_c/android/media/MediaFormat.c \
	test/o_c/android/media/PlaybackParams.c \
	test/o_c/android/os/Build.c \
	test/o_c/android/os/Bundle.c \
	test/o_c/tv/danmaku/ijk/media/player/misc/IMediaDataSource.c \
	test/o_c/tv/danmaku/ijk/media/player/IjkMediaPlayer.c \

test: cleantest j4a $(TEST_C)

cleantest:
	@rm -f $(TEST_C)



install: j4a
	@mkdir -p $(BINDIR)
	@cp ./j4a $(BINDIR)/j4a



# -----
.PHONY: all test clean install

clean:
	rm -f $(CXX_OBJS)
	rm -f $(DEPS)
	rm -f j4a
