#// --------------------------------------------------
#// FEATURE CONFIG
#// --------------------------------------------------
ifeq ($(CONFIG_S1G_HOOK), y)
DEFINE += -DINCLUDE_S1G_HOOK
DEFINE += -DINCLUDE_S1G_CONFIG
endif # CONFIG_S1G_HOOK

ifeq ($(CONFIG_UMAC_PRESP), y)
DEFINE += -DINCLUDE_UMAC_PRESP
endif # CONFIG_UMAC_PRESP

ifeq ($(CONFIG_MODEM_RECOVERY), y)
DEFINE += -DINCLUDE_MODEM_RECOVERY
#DEFINE += -DINCLUDE_OPTIMAL_CMD_SET
endif # CONFIG_MODEM_RECOVERY

ifeq ($(CONFIG_NEW_CHANNEL_CTX), y)
DEFINE += -DINCLUDE_NEW_CHANNEL_CTX
endif # CONFIG_NEW_CHANNEL_CTX

ifeq ($(CONFIG_APPLY_TX_GAIN_1_5_WITH_TXLO_TXIMG_CAL), y)
DEFINE	+= -DTX_GAIN_1_5_WITH_TXLO_TXIMG_CAL
endif # CONFIG_APPLY_TX_GAIN_1_5_WITH_TXLO_TXIMG_CAL

ifeq ($(CONFIG_USE_TEMP_SENSOR), y)
DEFINE	+= -DUSE_TEMP_SENSOR
endif # CONFIG_USE_TEMP_SENSOR

ifeq ($(CONFIG_MIC_SCAN), y)
DEFINE += -DINCLUDE_MIC_SCAN
endif # CONFIG_MIC_SCAN

ifeq ($(CONFIG_4M_OP_2M_TX), y)
DEFINE += -DINCLUDE_4M_OP_2M_TX
endif #CONFIG_4M_OP_2M_TX

ifeq ($(CONFIG_DUTYCYCLE), y)
DEFINE += -DINCLUDE_DUTYCYCLE
endif # CONFIG_DUTYCYCLE

ifeq ($(CONFIG_SILEX), y)
DEFINE += -DINCLUDE_SILEX
DEFINE += -DINCLUDE_GPIO_SILEX
endif # CONFIG_SILEX

ifeq ($(CONFIG_UCODE), y)
DEFINE += -DINCLUDE_UCODE
endif # CONFIG_UCODE

ifeq ($(CONFIG_UCODE7392), y)
DEFINE += -DINCLUDE_UCODE7392
endif # CONFIG_UCODE7392

ifeq ($(CONFIG_UCODE4791), y)
DEFINE += -DINCLUDE_UCODE4791
endif # CONFIG_UCODE4791

ifeq ($(CONFIG_TWT), y)
DEFINE += -DINCLUDE_TWT_SUPPORT

ifeq ($(CONFIG_MODEM_PS_HALT), y)
DEFINE += -DINCLUDE_MODEM_PS_HALT
endif # CONFIG_MODEM_PS_HALT

endif # CONFIG_TWT

ifeq ($(CONFIG_CONVERT_NON_QOSDATA), y)
DEFINE += -DINCLUDE_CONVERT_NON_QOSDATA
endif # CONFIG_CONVERT_NON_QOSDATA

ifeq ($(CONFIG_H2E), y)
DEFINE += -DINCLUDE_H2E_SUPPORT
endif # CONFIG_H2E

ifeq ($(CONFIG_WTS), y)
DEFINE += -DUMAC_CONFIG_WTS
endif # CONFIG_WTS
ifeq ($(CONFIG_BITMAP_ENCODING), y)
DEFINE += -DCONFIG_BITMAP_ENCODING
ifeq ($(CONFIG_REVERSE_SCRAMBLER), y)
DEFINE += -DCONFIG_REVERSE_SCRAMBLER
endif #CONFIG_REVERSE_SCRAMBLER
endif #CONFIG_BITMAP_ENCODING

ifeq ($(CONFIG_BG_SCAN), y)
DEFINE	+= -DCONFIG_BG_SCAN
endif # CONFIG_BG_SCAN

ifeq ($(CONFIG_PS_NONPOLL), y)
DEFINE += -DINCLUDE_PS_NONPOLL
endif # CONFIG_PS_NONPOLL

ifeq ($(CONFIG_BD), y)
DEFINE += -DINCLUDE_BD_SUPPORT
DEFINE += -DINCLUDE_BD_SUPPORT_TARGET_VERSION
endif # CONFIG_BD

ifeq ($(CONFIG_KR_MIC_CHANNEL),y)
DEFINE += -DINCLUDE_KR_MIC_CHANNEL
endif # CONFIG_KR_MIC_CHANNEL

ifeq ($(CONFIG_PMF_SWENC),y)
DEFINE += -DINCLUDE_PMF_SWENC
endif # CONFIG_PMF_SWENC

ifeq ($(CONFIG_RUNRAM),y)
DEFINE += -DINCLUDE_RUNRAM
endif # CONFIG_RUNRAM

ifeq ($(CONFIG_SET_WIM_BY_WQ),y)
DEFINE += -DINCLUDE_SET_WIM_BY_WQ
endif # CONFIG_SET_WIM_BY_WQ

ifeq ($(CONFIG_DL_TRANSMIT_BY_WQ),y)
DEFINE += -DINCLUDE_DL_TRANSMIT_BY_WQ
endif # CONFIG_DL_TRANSMIT_BY_WQ

ifeq ($(CONFIG_STA_SIG_INFO),y)
DEFINE += -DINCLUDE_STA_SIG_INFO
endif # CONFIG_STA_SIG_INFO

ifeq ($(CONFIG_WPS_PS_HOOK),y)
DEFINE += -DINCLUDE_WPS_PS_HOOK
endif # CONFIG_WPS_PS_HOOK

ifeq ($(CONFIG_1MBW_CENTER_LO),y)
DEFINE += -DINCLUDE_1MBW_CENTER_LO
#For 1M Bandwidth Center LO for EU
DEFINE += -DBW1M_CENTER_LO_EU
DEFINE += -DBW1M_CENTER_LO_JP
endif # CONFIG_1MBW_CENTER_LO

ifeq ($(CONFIG_PRIMASK_INT_LOCK),y)
DEFINE += -DINCLUDE_PRIMASK_INT_LOCK
endif # CONFIG_PRIMASK_INT_LOCK

ifeq ($(CONFIG_NEW_TASK_ARCH),y)
DEFINE += -DINCLUDE_NEW_TASK_ARCH
DEFINE += -DINCLUDE_NO_USE_LMAC_SEM
ifeq ($(CONFIG_WDT),y)
DEFINE += -DINCLUDE_WDT
endif # CONFIG_WDT
endif # CONFIG_NEW_TASK_ARCH

ifeq ($(CONFIG_MESH_HWENC),y)
DEFINE += -DINCLUDE_MESH_HWENC
endif # CONFIG_MESH_HWENC

ifeq ($(CONFIG_AVOID_FRAG_ATTACK),y)
DEFINE += -DINCLUDE_AVOID_FRAG_ATTACK
endif # CONFIG_AVOID_FRAG_ATTACK

ifeq ($(CONFIG_STA_CSA_SUPPORT),y)
DEFINE += -DINCLUDE_STA_CSA_SUPPORT
endif # CONFIG_STA_CSA_SUPPORT

ifeq ($(CONFIG_WOWLAN_PATTERN),y)
DEFINE += -DINCLUDE_WOWLAN_PATTERN
endif # CONFIG_WOWLAN_PATTERN

ifeq ($(CONFIG_FRAGMENT_FRAME),y)
DEFINE += -DINCLUDE_FRAG_FRAME
endif # CONFIG_FRAGMENT_FRAME

ifeq ($(CONFIG_CN_TEST_CH),y)
DEFINE += -DINCLUDE_CN_TEST_CH
endif # CONFIG_CN_TEST_CH

ifeq ($(CONFIG_RF_KILL),y)
DEFINE += -DINCLUDE_RF_KILL
endif # CONFIG_RF_KILL

ifeq ($(CONFIG_KR_USN_CHANNEL),y)
DEFINE += -DINCLUDE_1MBW_CENTER_LO
DEFINE += -DINCLUDE_KR_USN_CHANNEL
#For 1M Bandwidth Center LO for KR
DEFINE += -DBW1M_CENTER_LO_KR
DEFINE += -DINCLUDE_TEST_LBT_KR
endif #CONFIG_KR_USN_CHANNEL

ifeq ($(CONFIG_DMA_COPY),y)
DEFINE += -DINCLUDE_GDMA_COPY
endif #CONFIG_DMA_COPY

ifeq ($(CONFIG_SOFT_AP),y)
DEFINE += -DINCLUDE_SOFT_AP
DEFINE += -DSOFT_AP_BSS_MAX_IDLE
endif # CONFIG_SOFT_AP

ifeq ($(CONFIG_RTC_ALWAYS_ON),y)
DEFINE += -DINCLUDE_RTC_ALWAYS_ON
endif # CONFIG_RTC_ALWAYS_ON

