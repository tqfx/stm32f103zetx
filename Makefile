MAKEFLAGS += --silent

SOURCE_CLANG += src
SOURCE_CLANG += test

all: format

.PHONY: format clean

SOURCE_C := $(foreach v,$(SOURCE_CLANG),$(wildcard $(v)/*.[ch]))
SOURCE_CC := $(foreach v,$(SOURCE_CLANG),$(wildcard $(v)/*.[ch][ch]))
SOURCE_CXX := $(foreach v,$(SOURCE_CLANG),$(wildcard $(v)/*.[ch][xp][xp]))
format: $(SOURCE_C) $(SOURCE_CC) $(SOURCE_CXX)
	@$(foreach v,$^,$(shell clang-format -style=file -i $(v) --verbose))

clean:
	@-git clean -fdX
