.PHONY: src
.PHONY: test

src:
	$(MAKE) -C $@

test:
	$(MAKE) -C test $@
