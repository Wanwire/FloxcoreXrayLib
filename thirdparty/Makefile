
XRAY = Xray-core-25.5.16

default: $(XRAY)/patched

$(XRAY)/patched:
	@for patchfile in patches/libxray*.patch; do \
		git apply --check $$patchfile; \
		if [ $$? == 0 ]; then \
			git apply --whitespace=fix $$patchfile || true; \
		fi; \
	done;
	touch $(XRAY)/patched

clean:
	@git checkout $(XRAY)
	@git clean -dxf $(XRAY)

.PHONY: clean
