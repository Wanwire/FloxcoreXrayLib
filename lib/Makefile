# go/Makefile

XRAY := Xray-core-25.5.16
XRAY_DIR := $(CURDIR)/../thirdparty/$(XRAY)
CONFIGURATION_BUILD_DIR ?= $(CURDIR)/out
CONFIGURATION_TEMP_DIR ?= $(CURDIR)/.tmp
DESTDIR ?= $(CONFIGURATION_BUILD_DIR)
BUILDDIR ?= $(CONFIGURATION_TEMP_DIR)
PACKAGE := com.wanwire.libxraygo
LIB_NAME := libxray-go-android
JNI_LIB_NAME := libxray-jni
JAVA_CLASS_DIR := classes
AAR_DIR := $(BUILDDIR)/libxray-go-android
AAR_FILE := $(LIB_NAME).aar
AAP_PLATFORM := 21

ARCHS := arm64-v8a armeabi-v7a x86 x86_64
GO_SO_FILES := $(patsubst %,$(AAR_DIR)/jni/%/$(LIB_NAME).so,$(ARCHS))
JNI_SO_FILES := $(patsubst %,$(AAR_DIR)/jni/%/$(JNI_LIB_NAME).so,$(ARCHS))
JNI_INCLUDE := $(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include

GO := go
JAVAC := javac
JAR := jar
ZIP := zip

GOFLAGS := -ldflags="-s -w" -trimpath -v -buildmode=c-shared

default: $(DESTDIR)/$(AAR_FILE)

export GOPATH ?= $(shell PATH=$(PATH) go env GOPATH 2>/dev/null)
export REAL_GOROOT ?= $(shell PATH=$(PATH) go env GOROOT 2>/dev/null)
export GOROOT := $(BUILDDIR)/goroot
$(GOROOT)/.prepared:
	[ -n "$(REAL_GOROOT)" ]
	rm -rf "$(GOROOT)"
	mkdir -p "$(GOROOT)"
	mkdir -p "$(DESTDIR)"
	rsync -a --delete --exclude=pkg/obj/go-build "$(REAL_GOROOT)/" "$(GOROOT)/"
	touch "$@"

# Rule to build .so files for each architecture
$(AAR_DIR)/jni/arm64-v8a/$(JNI_LIB_NAME).so: src/xray_jni.c $(AAR_DIR)/jni/arm64-v8a/$(LIB_NAME).so
	@mkdir -p $(@D)
	@mv $(@D)/*.h $(@D)/libxray-go-android.h
	$(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/darwin-x86_64/bin/aarch64-linux-android$(AAP_PLATFORM)-clang $< -shared -Wl,-z,max-page-size=16384 -I$(JNI_INCLUDE) -o $@ -I $(@D) -L $(@D) -lxray-go-android
	@rm $(@D)/*.h

$(AAR_DIR)/jni/arm64-v8a/$(LIB_NAME).so: $(GOROOT)/.prepared $(XRAY_DIR)/go.mod
	@mkdir -p $(@D)
	@cd $(XRAY_DIR) && GOOS=android GOARCH=arm64 CGO_ENABLED=1 CC=$(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/darwin-x86_64/bin/aarch64-linux-android$(AAP_PLATFORM)-clang CGO_LDFLAGS="-O2 -s -w -Wl,-z,max-page-size=16384" \
		$(GO) build $(GOFLAGS) -o $@ ./main

$(AAR_DIR)/jni/armeabi-v7a/$(JNI_LIB_NAME).so: src/xray_jni.c $(AAR_DIR)/jni/armeabi-v7a/$(LIB_NAME).so
	@mkdir -p $(@D)
	@mv $(@D)/*.h $(@D)/libxray-go-android.h
	@$(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/darwin-x86_64/bin/armv7a-linux-androideabi$(AAP_PLATFORM)-clang $< -shared -Wl,-z,max-page-size=16384 -I$(JNI_INCLUDE) -o $@ -I $(@D) -L $(@D) -lxray-go-android
	@rm $(@D)/*.h

$(AAR_DIR)/jni/armeabi-v7a/$(LIB_NAME).so: $(GOROOT)/.prepared $(XRAY_DIR)/go.mod
	@mkdir -p $(@D)
	@cd $(XRAY_DIR) && GOOS=android GOARCH=arm CGO_ENABLED=1 CC=$(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/darwin-x86_64/bin/armv7a-linux-androideabi$(AAP_PLATFORM)-clang GOARM=7 CGO_LDFLAGS="-O2 -s -w -Wl,-z,max-page-size=16384" \
		$(GO) build $(GOFLAGS) -o $@ ./main

$(AAR_DIR)/jni/x86/$(JNI_LIB_NAME).so: src/xray_jni.c $(AAR_DIR)/jni/x86/$(LIB_NAME).so
	@mkdir -p $(@D)
	@mv $(@D)/*.h $(@D)/libxray-go-android.h
	@$(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/darwin-x86_64/bin/i686-linux-android$(AAP_PLATFORM)-clang $< -shared -Wl,-z,max-page-size=16384 -I$(JNI_INCLUDE) -o $@ -I $(@D) -L $(@D) -lxray-go-android
	@rm $(@D)/*.h

$(AAR_DIR)/jni/x86/$(LIB_NAME).so: $(GOROOT)/.prepared $(XRAY_DIR)/go.mod
	@mkdir -p $(@D)
	@cd $(XRAY_DIR) && GOOS=android GOARCH=386 CGO_ENABLED=1 CC=$(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/darwin-x86_64/bin/i686-linux-android$(AAP_PLATFORM)-clang CGO_LDFLAGS="-O2 -s -w -Wl,-z,max-page-size=16384" \
		$(GO) build $(GOFLAGS) -o $@ ./main

$(AAR_DIR)/jni/x86_64/$(JNI_LIB_NAME).so: src/xray_jni.c $(AAR_DIR)/jni/x86_64/$(LIB_NAME).so
	@mkdir -p $(@D)
	@mv $(@D)/*.h $(@D)/libxray-go-android.h
	@$(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/darwin-x86_64/bin/x86_64-linux-android$(AAP_PLATFORM)-clang $< -shared -Wl,-z,max-page-size=16384 -I$(JNI_INCLUDE) -o $@ -I $(@D) -L $(@D) -lxray-go-android
	@rm $(@D)/*.h

$(AAR_DIR)/jni/x86_64/$(LIB_NAME).so: $(GOROOT)/.prepared $(XRAY_DIR)/go.mod
	@mkdir -p $(@D)
	@cd $(XRAY_DIR) && GOOS=android GOARCH=amd64 CGO_ENABLED=1 CC=$(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/darwin-x86_64/bin/x86_64-linux-android$(AAP_PLATFORM)-clang CGO_LDFLAGS="-O2 -s -w -Wl,-z,max-page-size=16384"\
		$(GO) build $(GOFLAGS) -o $@ ./main

# Rules to compile the Java file
$(AAR_DIR)/$(JAVA_CLASS_DIR)/$(subst .,/,$(PACKAGE))/XrayGo.class: src/XrayGo.java
	@mkdir -p $(@D)
	$(JAVAC) -d $(AAR_DIR)/$(JAVA_CLASS_DIR) $<

#Rule to create classes.jar
$(AAR_DIR)/classes.jar: $(AAR_DIR)/$(JAVA_CLASS_DIR)/$(subst .,/,$(PACKAGE))/XrayGo.class
	@mkdir -p $(@D)
	cd $(AAR_DIR)/$(JAVA_CLASS_DIR) && $(JAR) cf $(AAR_DIR)/classes.jar com/wanwire/libxraygo/XrayGo.class

# Rule to create AndroidManifest.xml
$(AAR_DIR)/AndroidManifest.xml:
	@mkdir -p $(@D)
	@printf '<manifest xmlns:android="http://schemas.android.com/apk/res/android" package="$(PACKAGE)">\n</manifest>' > $@

# Rule to build the .aar file
$(AAR_DIR)/$(AAR_FILE): $(GO_SO_FILES) $(JNI_SO_FILES) $(AAR_DIR)/classes.jar $(AAR_DIR)/AndroidManifest.xml
	cd $(@D) && $(ZIP) -r $@ AndroidManifest.xml jni/ classes.jar

$(DESTDIR)/$(AAR_FILE): $(AAR_DIR)/$(AAR_FILE)
	@mkdir -p $(@D)
	cp $< $@

.PHONY: clean

clean:
	rm -rf $(AAR_DIR) $(JAVA_SRC_DIR) $(JAVA_CLASS_DIR) $(AAR_FILE) $(LIB_NAME)-*.so $(LIB_NAME)-*.h $(CONFIGURATION_TEMP_DIR)
