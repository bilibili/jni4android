include config.mak
CPPFLAGS = -g -std=c++11 -I./src -Wno-deprecated-register
YACC_FLAGS = --debug --verbose -d
YYLEX_FLAGS = 
J4A = ./j4a
ROOT_CLASS_INCLUDES = jni/j4a/j4a_allclasses.include.h
ROOT_CLASS_LOADERS = jni/j4a/j4a_allclasses.loader.h

all: j4a

CXX_SRCS = \
	src/ast_annotation.cpp \
	src/ast_argument.cpp \
	src/ast_class.cpp \
	src/ast_compilation_unit.cpp \
	src/ast_constructor.cpp \
	src/ast_field.cpp \
	src/ast_identifier.cpp \
	src/ast_member.cpp \
	src/ast_method.cpp \
	src/ast_node.cpp \
	src/ast_property_accessor.cpp \
	src/ast_reference_type.cpp \
	src/ast__context.cpp \
	src/ast__namespace.cpp \
	src/j4a_string_pool.cpp \
	src/j4a_string.cpp \
	src/flex.j4a.yy.cpp \
	src/bison.j4a.tab.cpp \
	src/main.cpp \

CXX_OBJS := $(CXX_SRCS:.cpp=.o)
CXX_DEPS := $(CXX_OBJS:.o=.d)
-include $(CXX_DEPS)

$(CXX_OBJS): config.mak config.h Makefile src/bison.j4a.tab.cpp src/flex.j4a.yy.cpp

$(CXX_OBJS): %.o: %.cpp
	$(CXX) $(CPPFLAGS) -MM -MT $@ -MF $(patsubst %.o,%.d,$@) $<
	$(CXX) $(CPPFLAGS) -c -o $@ $<

j4a: $(CXX_OBJS)
	$(CXX) -o j4a $(CXX_OBJS)



# YACC
YACC_DEPS = \
	src/bison.j4a.y \

src/bison.j4a.tab.cpp: $(YACC_DEPS)
	$(YACC) $(YACC_FLAGS) -o $@ src/bison.j4a.y

j4acc: src/bison.j4a.tab.cpp
	$(CXX) -o src/j4acc bison.j4a.tab.cpp


# YYLEX
YYLEX_DEPS = \
	src/flex.j4a.l \
	src/bison.j4a.tab.cpp \

src/flex.j4a.yy.cpp: $(YYLEX_DEPS)
	$(YYLEX) $(YYLEX_FLAGS) -o $@ src/flex.j4a.l

j4alex: src/flex.j4a.yy.cpp
	$(CXX) -o src/j4alex flex.j4a.yy.cpp


# test java -> c
TEST_JAVA_SRCS = \
	test/i_java/java/nio/Buffer.java \
	test/i_java/java/nio/ByteBuffer.java \
	test/i_java/java/util/ArrayList.java \
	test/i_java/android/media/AudioTrack.java \
	test/i_java/android/media/MediaCodec.java \
	test/i_java/android/media/MediaFormat.java \
	test/i_java/android/media/PlaybackParams.java \
	test/i_java/android/os/Build.java \
	test/i_java/android/os/Bundle.java \
	test/i_java/test/ReturnPrimitive.java \
	test/i_java/tv/danmaku/ijk/media/player/misc/IMediaDataSource.java \
	test/i_java/tv/danmaku/ijk/media/player/IjkMediaPlayer.java \

TEST_C_SRCS := $(TEST_JAVA_SRCS:test/i_java/%.java=jni/j4a/class/%.c)
TEST_H_SRCS := $(TEST_C_SRCS:%.c=%.h)

$(TEST_C_SRCS): jni/j4a/class/%.c: j4a

$(TEST_C_SRCS): jni/j4a/class/%.c: test/i_java/%.java
ifneq ("$<", "jni/j4a/class/.c")
	@mkdir -p $(shell dirname $@)
	$(J4A) -c $< -o $@
	@cat jni/j4a/class/$*.include.j4a >> $(ROOT_CLASS_INCLUDES)
	@echo >> $(ROOT_CLASS_INCLUDES)
	@cat jni/j4a/class/$*.loader.j4a >> $(ROOT_CLASS_LOADERS)
	@echo >> $(ROOT_CLASS_LOADERS)
	@#cp $@                 test/ref_c/$*.c
	@#cp jni/j4a/class/$*.h test/ref_c/$*.h
	@diff test/ref_c/$*.c 			$@
	@diff test/ref_c/$*.h 			jni/j4a/class/$*.h
	@diff test/ref_c/$*.include.j4a jni/j4a/class/$*.include.j4a 
	@diff test/ref_c/$*.loader.j4a  jni/j4a/class/$*.loader.j4a 
endif

test: j4a resettest $(TEST_C_SRCS)

resettest:
	@rm -f $(TEST_C_SRCS)
	@rm -f $(ROOT_CLASS_INCLUDES)
	@rm -f $(ROOT_CLASS_LOADERS)
	@mkdir -p jni
	@cp -r include/* jni/



install: j4a
	@mkdir -p $(BINDIR)
	@cp ./j4a $(BINDIR)/
	@mkdir -p $(INCDIR)
	@cp -r include/* $(INCDIR)/



# -----
.PHONY: all test clean install

clean: resettest
	rm -f $(CXX_OBJS)
	rm -f $(CXX_DEPS)
	rm -f j4a
