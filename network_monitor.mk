# network_monitor

NETWORK_MONITOR_VERSION = 1.0
NETWORK_MONITOR_SITE = package/network_monitor/src
NETWORK_MONITOR_SITE_METHOD = local

define NETWORK_MONITOR_BUILD_CMDS
	$(MAKE) \
		CC="$(TARGET_CC)" \
		CFLAGS="$(TARGET_CFLAGS) -Iinclude" \
		-C $(@D)
endef

define NETWORK_MONITOR_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/network_monitor \
		$(TARGET_DIR)/usr/bin/network_monitor

	$(INSTALL) -D -m 0755 \
		$(NETWORK_MONITOR_PKGDIR)/S99network_monitor \
		$(TARGET_DIR)/etc/init.d/S99network_monitor
        $(INSTALL) -D -m 0644 \
                 $(NETWORK_MONITOR_PKGDIR)/rootfs_overlay/etc/network_monitor.conf \
                 $(TARGET_DIR)/etc/network_monitor.conf
endef
$(eval $(generic-package))
