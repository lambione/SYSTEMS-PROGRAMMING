CXXFLAGS = -Wall -std=c++11
CFLAGS = -Wall

.PHONY: all
all: keywords

.PHONY: test
test: test_keywords.sh keywords 
	./test_keywords.sh

.PHONY: submit
submit: submission.tar.gz
submission.tar.gz:
	mkdir submission
	touch README
	cp keywords.* README submission/
	tar cf - submission | gzip > $@
	rm -f submission
