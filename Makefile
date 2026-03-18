default:
	PATH="$(PATH):$(HOME)/go/bin" go install golang.org/x/mobile/cmd/gomobile@latest
	PATH="$(PATH):$(HOME)/go/bin" gomobile init
	PATH="$(PATH):$(HOME)/go/bin" CGO_LDFLAGS="-Wl,-z,max-page-size=16384" gomobile bind -v -androidapi 21 -trimpath -ldflags='-s -w -buildid=' ./

clean:
	@rm -f *.aar *.jar

.PHONY: clean
