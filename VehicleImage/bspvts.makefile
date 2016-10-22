# The file "bspvts.makefile" is the external makefile fragment used by the
# Wind River Workbench to invoke the scripts for BSP VTS.
# It contains all special rules for redirection to vxtest runs.

BSPVTS_SUITE_OPTION := -suite $(BSPVTS_SUITE)

BSPVTS_PROJECT_OPTION := -project $(CURDIR)

BSPVTS_CONFIGDIR_OPTION :=
ifneq ($(BSPVTS_CONFIGDIR),)
	BSPVTS_CONFIGDIR_OPTION := -configDir $(subst \,/,$(BSPVTS_CONFIGDIR))
endif

BSPVTS_BOARD_OPTION := -template $(BSPVTS_BOARD)
ifeq ($(BSPVTS_USE_BARCODE),1)
	BSPVTS_BOARD_OPTION := -barcode $(BSPVTS_BOARD)
endif

BSPVTS_HOST_OPTION :=
ifneq ($(BSPVTS_HOST),)
	BSPVTS_HOST_OPTION := -host $(BSPVTS_HOST)
endif

BSPVTS_HOST_OPTIONS := $(BSPVTS_HOST_OPTION)
ifneq ($(BSPVTS_HOSTIP),)
	BSPVTS_HOST_OPTIONS += -hostIp $(BSPVTS_HOSTIP)
endif
ifneq ($(BSPVTS_USER),)
	BSPVTS_HOST_OPTIONS += -user $(BSPVTS_USER)
endif
ifneq ($(BSPVTS_PASSWORD),)
	BSPVTS_HOST_OPTIONS += -password $(BSPVTS_PASSWORD)
endif

BSPVTS_BSPTOOLBOARD_OPTION := -bspToolBoard $(BSP_DIR) $(TOOL) $(BSPVTS_BOARD)

BSPVTS_TIMEOUT_OPTION :=
ifneq ($(BSPVTS_TIMEOUT),)
	BSPVTS_TIMEOUT_OPTION := -testMsgTimeout $(BSPVTS_TIMEOUT)
endif

BSPVTS_HTMLDIR_OPTION :=
ifneq ($(BSPVTS_HTMLDIR),)
	BSPVTS_HTMLDIR_OPTION := -htmlDir $(subst \,/,$(BSPVTS_HTMLDIR))
endif

vxtest_suite_config :
	@echo "make: invoking VxTest suite configuration..."
	vxtest suiteConfig $(BSPVTS_SUITE_OPTION) $(BSPVTS_PROJECT_OPTION) $(BSPVTS_CONFIGDIR_OPTION)

vxtest_board_config :
	@echo "make: invoking VxTest board configuration..."
	vxtest boardConfig $(BSPVTS_BOARD_OPTION) $(BSPVTS_PROJECT_OPTION) $(BSPVTS_CONFIGDIR_OPTION)

vxtest_host_config :
	@echo "make: invoking VxTest host configuration..."
	vxtest hostConfig $(BSPVTS_HOST_OPTIONS) $(BSPVTS_PROJECT_OPTION) $(BSPVTS_CONFIGDIR_OPTION)

vxtest_suite_build : vxtest_suite_config
	@echo "make: invoking VxTest suite build..."
	vxtest suiteBuild -v $(BSPVTS_SUITE_OPTION) $(BSPVTS_BSPTOOLBOARD_OPTION) $(BSPVTS_PROJECT_OPTION) $(BSPVTS_CONFIGDIR_OPTION)

vxtest_suite_run : vxtest_host_config
	@echo "make: invoking VxTest suite run..."
	vxtest suiteRun -v $(BSPVTS_SUITE_OPTION) $(BSPVTS_HOST_OPTION) $(BSPVTS_BSPTOOLBOARD_OPTION) $(BSPVTS_TIMEOUT_OPTION) $(BSPVTS_PROJECT_OPTION) $(BSPVTS_CONFIGDIR_OPTION)

vxtest_suite_results :
	@echo "make: invoking VxTest suite results..."
	vxtest suiteResults -v $(BSPVTS_SUITE_OPTION) $(BSPVTS_HTMLDIR_OPTION) $(BSPVTS_PROJECT_OPTION) $(BSPVTS_CONFIGDIR_OPTION)
