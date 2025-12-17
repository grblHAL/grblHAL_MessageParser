/*
  config.h - compile time configuration, see note below
  Part of grblHAL

  Copyright (c) 2019-2025 Terje Io
  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2009-2011 Simen Svale Skogsrud

  grblHAL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  grblHAL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with grblHAL. If not, see <http://www.gnu.org/licenses/>.
*/

// NOTE: This file contains parts of various files copied from grbl for use by MPG/DRO processor

// Define realtime command special characters. These characters are 'picked-off' directly from the
// serial read data stream and are not passed to the grbl line execution parser. Select characters
// that do not and must not exist in the streamed g-code program. ASCII control characters may be
// used, if they are available per user setup. Also, extended ASCII codes (>127), which are never in
// g-code programs, maybe selected for interface programs.
// NOTE: If changed, manually update help message in report.c.

#define CMD_EXIT                    0x03 //!< ctrl-C (ETX)
#define CMD_REBOOT                  0x14 //!< ctrl-T (DC4) - only acted upon if preceded by 0x1B (ESC)
#define CMD_RESET                   0x18 //!< ctrl-X (CAN)
#define CMD_STOP                    0x19 //!< ctrl-Y (EM)
#define CMD_STATUS_REPORT_LEGACY    '?'
#define CMD_CYCLE_START_LEGACY      '~'
#define CMD_FEED_HOLD_LEGACY        '!'
#define CMD_PROGRAM_DEMARCATION     '%'

// NOTE: All override realtime commands must be in the extended ASCII character set, starting
// at character value 128 (0x80) and up to 255 (0xFF). If the normal set of realtime commands,
// such as status reports, feed hold, reset, and cycle start, are moved to the extended set
// space, protocol.c's protocol_process_realtime() will need to be modified to accommodate the change.
#define CMD_STATUS_REPORT                   0x80 // (128) TODO: use 0x05 ctrl-E ENQ instead?
#define CMD_CYCLE_START                     0x81 // (129) TODO: use 0x06 ctrl-F ACK instead? or SYN/DC2/DC3?
#define CMD_FEED_HOLD                       0x82 // (130) TODO: use 0x15 ctrl-U NAK instead?
#define CMD_GCODE_REPORT                    0x83 // (131)
#define CMD_SAFETY_DOOR                     0x84 // (132)
#define CMD_JOG_CANCEL                      0x85 // (133)
//#define CMD_DEBUG_REPORT 0x86 // Only when DEBUG enabled, sends debug report in '{}' braces.
#define CMD_STATUS_REPORT_ALL               0x87 // (135)
#define CMD_OPTIONAL_STOP_TOGGLE            0x88 // (136)
#define CMD_SINGLE_BLOCK_TOGGLE             0x89 // (137)
#define CMD_OVERRIDE_FAN0_TOGGLE            0x8A //!< (138) Toggle Fan 0 on/off, not implemented by the core.
#define CMD_MPG_MODE_TOGGLE                 0x8B //!< (139) Toggle MPG mode on/off, available when the MPG stream is enabled with MPG mode 2.
#define CMD_AUTO_REPORTING_TOGGLE           0x8C //!< (140) Toggle auto real time reporting if configured.
#define CMD_OVERRIDE_FEED_RESET             0x90 //!< (144) Restores feed override value to 100%.
#define CMD_OVERRIDE_FEED_COARSE_PLUS       0x91 // (145)
#define CMD_OVERRIDE_FEED_COARSE_MINUS      0x92 // (146)
#define CMD_OVERRIDE_FEED_FINE_PLUS         0x93 // (147)
#define CMD_OVERRIDE_FEED_FINE_MINUS        0x94 // (148)
#define CMD_OVERRIDE_RAPID_RESET            0x95 //!< (149) Restores rapid override value to 100%.
#define CMD_OVERRIDE_RAPID_MEDIUM           0x96 // (150)
#define CMD_OVERRIDE_RAPID_LOW              0x97 // (151)
// #define CMD_OVERRIDE_RAPID_EXTRA_LOW 0x98 // *NOT SUPPORTED*
#define CMD_OVERRIDE_SPINDLE_RESET 			0x99 // (153) Restores spindle override value to 100%.
#define CMD_OVERRIDE_SPINDLE_COARSE_PLUS    0x9A // (154)
#define CMD_OVERRIDE_SPINDLE_COARSE_MINUS   0x9B // (155)
#define CMD_OVERRIDE_SPINDLE_FINE_PLUS      0x9C // (156)
#define CMD_OVERRIDE_SPINDLE_FINE_MINUS     0x9D // (157)
#define CMD_OVERRIDE_SPINDLE_STOP           0x9E // (158)
#define CMD_OVERRIDE_COOLANT_FLOOD_TOGGLE   0xA0 // (160)
#define CMD_OVERRIDE_COOLANT_MIST_TOGGLE    0xA1 // (161)
#define CMD_PID_REPORT                      0xA2 // (162)
#define CMD_TOOL_ACK                        0xA3 // (163)
#define CMD_PROBE_CONNECTED_TOGGLE          0xA4 // (164)
// The following character codes are reserved for plugin use
#define CMD_MACRO_0 						0xB0 // (176)
#define CMD_MACRO_1 						0xB1 // (177)
#define CMD_MACRO_2 						0xB2 // (178)
#define CMD_MACRO_3 						0xB3 // (179)
#define CMD_MACRO_4 						0xB4 // (180)
#define CMD_MACRO_5 						0xB5 // (181)
#define CMD_MACRO_6 						0xB6 // (182)
#define CMD_MACRO_7 						0xB7 // (183)

#define MAX_STORED_LINE_LENGTH 80

typedef enum {
    SystemState_Idle = 0,
    SystemState_Alarm = 1,
    SystemState_CheckMode = 2,
    SystemState_Homing = 3,
    SystemState_Cycle = 4,
    SystemState_Hold = 5,
    SystemState_Jog = 6,
    SystemState_DoorOpen = 7,
    SystemState_Sleep = 8,
    SystemState_EStop = 9,
    SystemState_ToolChange = 10,
    SystemState_Undefined = 255
} __attribute__ ((__packed__)) system_state_t;

// Define grblHAL status codes. Valid values (0-255)
// Code 0 - 38 is equal to legacy Grbl codes
typedef enum {
    Status_OK = 0,
    Status_ExpectedCommandLetter = 1,
    Status_BadNumberFormat = 2,
    Status_InvalidStatement = 3,
    Status_NegativeValue = 4,
    Status_HomingDisabled = 5,
    Status_SettingStepPulseMin = 6,
    Status_SettingReadFail = 7,
    Status_IdleError = 8,
    Status_SystemGClock = 9,
    Status_SoftLimitError = 10,
    Status_Overflow = 11,
    Status_MaxStepRateExceeded = 12,
    Status_CheckDoor = 13,
    Status_LineLengthExceeded = 14,
    Status_TravelExceeded = 15,
    Status_InvalidJogCommand = 16,
    Status_SettingDisabledLaser = 17,
    Status_Reset = 18,
    Status_NonPositiveValue = 19,

    Status_GcodeUnsupportedCommand = 20,
    Status_GcodeModalGroupViolation = 21,
    Status_GcodeUndefinedFeedRate = 22,
    Status_GcodeCommandValueNotInteger = 23,
    Status_GcodeAxisCommandConflict = 24,
    Status_GcodeWordRepeated = 25,
    Status_GcodeNoAxisWords = 26,
    Status_GcodeInvalidLineNumber = 27,
    Status_GcodeValueWordMissing = 28,
    Status_GcodeUnsupportedCoordSys = 29,
    Status_GcodeG53InvalidMotionMode = 30,
    Status_GcodeAxisWordsExist = 31,
    Status_GcodeNoAxisWordsInPlane = 32,
    Status_GcodeInvalidTarget = 33,
    Status_GcodeArcRadiusError = 34,
    Status_GcodeNoOffsetsInPlane = 35,
    Status_GcodeUnusedWords = 36,
    Status_GcodeG43DynamicAxisError = 37,
    Status_GcodeIllegalToolTableEntry = 38,
    Status_GcodeValueOutOfRange = 39,
    Status_GcodeToolChangePending = 40,
    Status_GcodeSpindleNotRunning = 41,
    Status_GcodeIllegalPlane = 42,
    Status_GcodeMaxFeedRateExceeded = 43,
    Status_GcodeRPMOutOfRange = 44,
    Status_LimitsEngaged = 45,
    Status_HomingRequired = 46,
    Status_GCodeToolError = 47,
    Status_ValueWordConflict = 48,
    Status_SelfTestFailed = 49,
    Status_EStop = 50,
    Status_MotorFault = 51,
    Status_SettingValueOutOfRange = 52,
    Status_SettingDisabled = 53,
    Status_GcodeInvalidRetractPosition = 54,
    Status_IllegalHomingConfiguration = 55,
    Status_GCodeCoordSystemLocked = 56,
    Status_UnexpectedDemarcation = 57,
    Status_AuxiliaryPortUnavailable = 58,

    Status_SDMountError = 60,
    Status_FileReadError = 61,
    Status_FsFailedOpenDir = 62,
    Status_FSDirNotFound = 63,
    Status_SDNotMounted = 64,
    Status_FsNotMounted = 65,
    Status_FsReadOnly = 66,

    Status_BTInitError = 70,

//
    Status_ExpressionUknownOp = 71,
    Status_ExpressionDivideByZero = 72,
    Status_ExpressionArgumentOutOfRange = 73,
    Status_ExpressionInvalidArgument = 74,
    Status_ExpressionSyntaxError = 75,
    Status_ExpressionInvalidResult = 76,

    Status_AuthenticationRequired = 77,
    Status_AccessDenied = 78,
    Status_NotAllowedCriticalEvent = 79,

    Status_FlowControlNotExecutingMacro = 80,
    Status_FlowControlSyntaxError = 81,
    Status_FlowControlStackOverflow = 82,
    Status_FlowControlOutOfMemory = 83,
    Status_FileOpenFailed = 84,
    Status_FsFormatFailed = 85,
    Status_AuxiliaryPortUnusable = 86,
    Status_StatusMax = Status_AuxiliaryPortUnusable,
    Status_UserException = 253,
    Status_Handled,   // For internal use only
    Status_Unhandled  // For internal use only
} __attribute__ ((__packed__)) status_code_t;

// Alarm codes. Valid values (1-255). Zero is reserved.
// Code 0 - 9 is equal to legacy Grbl codes, 15 equals legacy Grbl code 10
typedef enum {
    Alarm_None = 0,                             //!< 0
    Alarm_HardLimit = 1,                        //!< 1
    Alarm_SoftLimit = 2,                        //!< 2
    Alarm_AbortCycle = 3,                       //!< 3
    Alarm_ProbeFailInitial = 4,                 //!< 4
    Alarm_ProbeFailContact = 5,                 //!< 5
    Alarm_HomingFailReset = 6,                  //!< 6
    Alarm_HomingFailDoor = 7,                   //!< 7
    Alarm_FailPulloff = 8,                      //!< 8
    Alarm_HomingFailApproach = 9,               //!< 9
    Alarm_EStop = 10,                           //!< 10
    Alarm_HomingRequired = 11,                  //!< 11
    Alarm_LimitsEngaged = 12,                   //!< 12
    Alarm_ProbeProtect = 13,                    //!< 13
    Alarm_Spindle = 14,                         //!< 14
    Alarm_HomingFailAutoSquaringApproach = 15,  //!< 15
    Alarm_SelftestFailed = 16,                  //!< 16
    Alarm_MotorFault = 17,                      //!< 17
    Alarm_HomingFail = 18,                      //!< 18
    Alarm_ModbusException = 19,                 //!< 19
    Alarm_ExpanderException = 20,               //!< 20
    Alarm_AlarmMax = Alarm_ExpanderException
} __attribute__ ((__packed__)) alarm_code_t;

typedef enum {
    Setting_PulseMicroseconds = 0,
    Setting_StepperIdleLockTime = 1,
    Setting_StepInvertMask = 2,
    Setting_DirInvertMask = 3,
    Setting_InvertStepperEnable = 4,
    Setting_LimitPinsInvertMask = 5,
    Setting_InvertProbePin = 6,
    Setting_SpindlePWMBehaviour = 7, // Deprecated - replaced by Setting_SpindlePWMOptions flag
    Setting_GangedDirInvertMask = 8,
    Setting_SpindlePWMOptions = 9,
    Setting_StatusReportMask = 10,
    Setting_JunctionDeviation = 11,
    Setting_ArcTolerance = 12,
    Setting_ReportInches = 13,
    Setting_ControlInvertMask = 14,
    Setting_CoolantInvertMask = 15,
    Setting_SpindleInvertMask = 16,
    Setting_ControlPullUpDisableMask = 17,
    Setting_LimitPullUpDisableMask = 18,
    Setting_ProbePullUpDisable = 19,
    Setting_SoftLimitsEnable = 20,
    Setting_HardLimitsEnable = 21,
    Setting_HomingEnable = 22,
    Setting_HomingDirMask = 23,
    Setting_HomingFeedRate = 24,
    Setting_HomingSeekRate = 25,
    Setting_HomingDebounceDelay = 26,
    Setting_HomingPulloff = 27,
    Setting_G73Retract = 28,
    Setting_PulseDelayMicroseconds = 29,
    Setting_RpmMax = 30,
    Setting_RpmMin = 31,
    Setting_Mode = 32,
    Setting_PWMFreq = 33,
    Setting_PWMOffValue = 34,
    Setting_PWMMinValue = 35,
    Setting_PWMMaxValue = 36,
    Setting_SteppersEnergize = 37,
    Setting_SpindlePPR = 38,
    Setting_EnableLegacyRTCommands = 39,
    Setting_JogSoftLimited = 40,
    Setting_ParkingEnable = 41,
    Setting_ParkingAxis = 42,

    Setting_HomingLocateCycles = 43,
    Setting_HomingCycle_1 = 44,
    Setting_HomingCycle_2 = 45,
    Setting_HomingCycle_3 = 46,
    Setting_HomingCycle_4 = 47,
    Setting_HomingCycle_5 = 48,
    Setting_HomingCycle_6 = 49,
// Optional driver implemented settings for jogging
    Setting_JogStepSpeed = 50,
    Setting_JogSlowSpeed = 51,
    Setting_JogFastSpeed = 52,
    Setting_JogStepDistance = 53,
    Setting_JogSlowDistance = 54,
    Setting_JogFastDistance = 55,
//
    Setting_ParkingPulloutIncrement = 56,
    Setting_ParkingPulloutRate = 57,
    Setting_ParkingTarget = 58,
    Setting_ParkingFastRate = 59,

    Setting_RestoreOverrides = 60,
    Setting_DoorOptions = 61,
    Setting_SleepEnable = 62,
    Setting_HoldActions = 63,
    Setting_ForceInitAlarm = 64,
    Setting_ProbingFlags = 65,
// Optional driver implemented settings for piecewise linear spindle PWM algorithm
    Setting_LinearSpindlePiece1 = 66,
    Setting_LinearSpindlePiece2 = 67,
    Setting_LinearSpindlePiece3 = 68,
    Setting_LinearSpindlePiece4 = 69,
//

// Optional driver implemented settings for additional streams
    Setting_NetworkServices = 70,
    Setting_BlueToothDeviceName = 71,
    Setting_BlueToothServiceName = 72,
    Setting_WifiMode = 73,
    Setting_WiFi_STA_SSID = 74,
    Setting_WiFi_STA_Password = 75,
    Setting_WiFi_AP_SSID = 76,
    Setting_WiFi_AP_Password = 77,
    Setting_Wifi_AP_Country = 78,
    Setting_Wifi_AP_Channel = 79,
//

// Optional settings for closed loop spindle speed control
    Setting_SpindlePGain = 80,
    Setting_SpindleIGain = 81,
    Setting_SpindleDGain = 82,
    Setting_SpindleDeadband = 83,
    Setting_SpindleMaxError = 84,
    Setting_SpindleIMaxError = 85,
    Setting_SpindleDMaxError = 86,

// Optional settings for closed loop spindle synchronized motion
    Setting_PositionPGain = 90,
    Setting_PositionIGain = 91,
    Setting_PositionDGain = 92,
    Setting_PositionDeadband = 93,
    Setting_PositionMaxError = 94,
    Setting_PositionIMaxError = 95,
    Setting_PositionDMaxError = 96,
//

// Reserving settings in the range 100 - 299 for axis settings.
    Setting_AxisSettingsBase = 100,     // Reserved for core settings
    Setting_AxisSettingsMax = Setting_AxisSettingsBase + AXIS_SETTINGS_INCREMENT * 9 + N_AXIS,
    Setting_AxisSettingsBase2 = 200,    // Reserved for driver/plugin settings
    Setting_AxisSettingsMax2 = Setting_AxisSettingsBase2 + AXIS_SETTINGS_INCREMENT * 9 + N_AXIS,
//

// Optional driver implemented settings

    // Normally used for Ethernet
    Setting_Hostname = 300,
    Setting_IpMode = 301,
    Setting_IpAddress = 302,
    Setting_Gateway = 303,
    Setting_NetMask = 304,
    Setting_TelnetPort = 305,
    Setting_HttpPort = 306,
    Setting_WebSocketPort = 307,
    Setting_FtpPort = 308,

    // Normally used for WiFi Access Point
    Setting_Hostname2 = 310,
    Setting_IpMode2 = 311,
    Setting_IpAddress2 = 312,
    Setting_Gateway2 = 313,
    Setting_NetMask2 = 314,
    Setting_TelnetPort2 = 315,
    Setting_HttpPort2 = 316,
    Setting_WebSocketPort2 = 317,
    Setting_FtpPort2 = 318,

    // Normally used for WiFi Station
    Setting_Hostname3 = 320,
    Setting_IpMode3 = 321,
    Setting_IpAddress3 = 322,
    Setting_Gateway3 = 323,
    Setting_NetMask3 = 324,
    Setting_TelnetPort3 = 325,
    Setting_HttpPort3 = 326,
    Setting_WebSocketPort3 = 327,
    Setting_FtpPort3 = 328,

    Setting_AdminPassword = 330,
    Setting_UserPassword = 331,
    Setting_NTPServerURI = 332,
    Setting_NTPServerURI_2 = 333,
    Setting_NTPServerURI_3 = 334,
    Setting_Timezone = 335,
    Setting_DSTActive = 336,

    Setting_Wifi_AP_BSSID = 337,

    Setting_TrinamicDriver = 338,
    Setting_TrinamicHoming = 339,

    Setting_SpindleAtSpeedTolerance = 340,
    Setting_ToolChangeMode = 341,
    Setting_ToolChangeProbingDistance = 342,
    Setting_ToolChangeFeedRate = 343,
    Setting_ToolChangeSeekRate = 344,
    Setting_ToolChangePulloffRate = 345,
    Setting_ToolChangeOptions = 346,

    Setting_DualAxisLengthFailPercent = 347,
    Setting_DualAxisLengthFailMin = 348,
    Setting_DualAxisLengthFailMax = 349,

    Setting_THC_Mode = 350,
    Setting_THC_Delay = 351,
    Setting_THC_Threshold = 352,
    Setting_THC_PGain = 353,
    Setting_THC_IGain = 354,
    Setting_THC_DGain = 355,
    Setting_THC_VADThreshold = 356,
    Setting_THC_VoidOverride = 357,
    Setting_Arc_FailTimeout = 358,
    Setting_Arc_RetryDelay = 359,
    Setting_Arc_MaxRetries = 360,
    Setting_Arc_VoltageScale = 361,
    Setting_Arc_VoltageOffset = 362,
    Setting_Arc_HeightPerVolt = 363,
    Setting_Arc_OkHighVoltage = 364,
    Setting_Arc_OkLowVoltage = 365,
    Setting_Arc_VoltagePort = 366,
    Setting_Arc_OkPort = 367,
    Setting_THC_CutterDownPort = 368,
    Setting_THC_CutterUpPort = 369,

    Settings_IoPort_InvertIn  = 370,
    Settings_IoPort_Pullup_Disable = 371,
    Settings_IoPort_InvertOut = 372,
    Settings_IoPort_OD_Enable = 373,
    Settings_ModBus_BaudRate = 374,
    Settings_ModBus_RXTimeout = 375,
    Settings_RotaryAxes = 376,
    Setting_BlueToothInitOK = 377,
    Setting_LaserCoolantOnDelay = 378,
    Setting_LaserCoolantOffDelay = 379,
    Setting_LaserCoolantMinTemp = 380,
    Setting_LaserCoolantMaxTemp = 381,
    Setting_LaserCoolantOffset = 382,
    Setting_LaserCoolantGain = 383,
    Setting_DisableG92Persistence = 384,
    Setting_BlueToothStateInput = 385,
    Setting_FanPort0 = 386,
    Setting_FanPort1 = 387,
    Setting_FanPort2 = 388,
    Setting_FanPort3 = 389,
    Setting_LaserCoolantTempPort = 390,
    Setting_LaserCoolantOkPort = 391,
    Setting_DoorSpindleOnDelay = 392,
    Setting_DoorCoolantOnDelay = 393,
    Setting_SpindleOnDelay = 394,
    Setting_SpindleType = 395,
    Setting_WebUiTimeout = 396,
    Setting_WebUiAutoReportInterval = 397,
    Setting_PlannerBlocks = 398,
    Setting_CANbus_BaudRate = 399,

    Setting_EncoderSettingsBase = 400, // NOTE: Reserving settings values >= 400 for encoder settings. Up to 449.
    Setting_EncoderSettingsMax = 449,

    // Reserved for user plugins - do NOT use for public plugins
    Setting_UserDefined_0 = 450,
    Setting_UserDefined_1 = 451,
    Setting_UserDefined_2 = 452,
    Setting_UserDefined_3 = 453,
    Setting_UserDefined_4 = 454,
    Setting_UserDefined_5 = 455,
    Setting_UserDefined_6 = 456,
    Setting_UserDefined_7 = 457,
    Setting_UserDefined_8 = 458,
    Setting_UserDefined_9 = 459,

    Setting_VFD_ModbusAddress = 460,
    Setting_VFD_RPM_Hz = 461,
    Setting_VFD_10 = 462,
    Setting_VFD_11 = 463,
    Setting_VFD_12 = 464,
    Setting_VFD_13 = 465,
    Setting_VFD_14 = 466,
    Setting_VFD_15 = 467,
    Setting_VFD_16 = 468,
    Setting_VFD_17 = 469,
    Setting_VFD_18 = 470,
    Setting_VFD_19 = 471,
    Setting_VFD_20 = 472,
    Setting_VFD_21 = 473,

    Setting_VFD_ModbusAddress0 = 476,
    Setting_VFD_ModbusAddress1 = 477,
    Setting_VFD_ModbusAddress2 = 478,
    Setting_VFD_ModbusAddress3 = 479,

    Setting_Fan0OffDelay = 480,
    Setting_AutoReportInterval = 481,
    Setting_TimeZoneOffset = 482,
    Setting_FanToSpindleLink = 483,
    Setting_UnlockAfterEStop = 484,
    Setting_EnableToolPersistence = 485,
    Setting_OffsetLock = 486,
    Setting_Spindle_OnPort = 487,
    Setting_Spindle_DirPort = 488,
    Setting_Spindle_PWMPort = 489,

    Setting_Macro0    = 490,
    Setting_MacroBase = Setting_Macro0,
    Setting_Macro1    = 491,
    Setting_Macro2    = 492,
    Setting_Macro3    = 493,
    Setting_Macro4    = 494,
    Setting_Macro5    = 495,
    Setting_Macro6    = 496,
    Setting_Macro7    = 497,
    Setting_Macro8    = 498,
    Setting_Macro9    = 499,

    Setting_MacroPort0    = 500,
    Setting_MacroPortBase = Setting_MacroPort0,
    Setting_MacroPort1    = 501,
    Setting_MacroPort2    = 502,
    Setting_MacroPort3    = 503,
    Setting_MacroPort4    = 504,
    Setting_MacroPort5    = 505,
    Setting_MacroPort6    = 506,
    Setting_MacroPort7    = 507,
    Setting_MacroPort8    = 508,
    Setting_MacroPort9    = 509,

    Setting_SpindleEnable0    = 510,
    Setting_SpindleEnableBase = Setting_SpindleEnable0,
    Setting_SpindleEnable1    = 511,
    Setting_SpindleEnable2    = 512,
    Setting_SpindleEnable3    = 513,
    Setting_SpindleEnable4    = 514,
    Setting_SpindleEnable5    = 515,
    Setting_SpindleEnable6    = 516,
    Setting_SpindleEnable7    = 517,
    Setting_EncoderSpindle    = 519,

    Setting_SpindleToolStart0    = 520,
    Setting_SpindleToolStartBase = Setting_SpindleToolStart0,
    Setting_SpindleToolStart1    = 521,
    Setting_SpindleToolStart2    = 522,
    Setting_SpindleToolStart3    = 523,
    Setting_SpindleToolStart4    = 524,
    Setting_SpindleToolStart5    = 525,
    Setting_SpindleToolStart6    = 526,
    Setting_SpindleToolStart7    = 527,

    Setting_MQTTBrokerIpAddress = 530,
    Setting_MQTTBrokerPort      = 531,
    Setting_MQTTBrokerUserName  = 532,
    Setting_MQTTBrokerPassword  = 533,

    Setting_NGCDebugOut = 534,
    Setting_NetworkMAC = 535,
    Setting_RGB_StripLengt0 = 536,
    Setting_RGB_StripLengt1 = 537,
    Setting_RotaryWrap = 538,
    Setting_SpindleOffDelay = 539,

    Setting_Panel_SpindleSpeed       = 540,  // NOTE: Reserving settings values 540 to 579 for panel settings.
    Setting_Panel_ModbusAddress      = 541,
    Setting_Panel_UpdateInterval     = 542,
    Setting_Panel_JogSpeed_x1        = 543,
    Setting_Panel_JogSpeed_x10       = 544,
    Setting_Panel_JogSpeed_x100      = 545,
    Setting_Panel_JogSpeed_Keypad    = 546,
    Setting_Panel_JogDistance_x1     = 547,
    Setting_Panel_JogDistance_x10    = 548,
    Setting_Panel_JogDistance_x100   = 549,
    Setting_Panel_JogDistance_Keypad = 550,
    Setting_Panel_JogAccelRamp       = 551,
    Setting_Panel_Encoder0_Mode      = 552,
    Setting_Panel_Encoder0_Cpd       = 553,
    Setting_Panel_Encoder1_Mode      = 554,
    Setting_Panel_Encoder1_Cpd       = 555,
    Setting_Panel_Encoder2_Mode      = 556,
    Setting_Panel_Encoder2_Cpd       = 557,
    Setting_Panel_Encoder3_Mode      = 558,
    Setting_Panel_Encoder3_Cpd       = 559,
    Setting_Panel_SettingsMax        = 579,

    Setting_ButtonAction0    = 590,
    Setting_ButtonActionBase = Setting_ButtonAction0,
    Setting_ButtonAction1    = 591,
    Setting_ButtonAction2    = 592,
    Setting_ButtonAction3    = 593,
    Setting_ButtonAction4    = 594,
    Setting_ButtonAction5    = 595,
    Setting_ButtonAction6    = 596,
    Setting_ButtonAction7    = 597,
    Setting_ButtonAction8    = 598,
    Setting_ButtonAction9    = 599,

    Setting_ModbusTCPBase       = 600,    // Reserving settings values 600 to 639 for ModBus TCP (8 sets)
    Setting_ModbusIpAddressBase = Setting_ModbusTCPBase + Setting_ModbusIpAddress,
    Setting_ModbusPortBase      = Setting_ModbusTCPBase + Setting_ModbusPort,
    Setting_ModbusIdBase        = Setting_ModbusTCPBase + Setting_ModbusId,
    Setting_ModbusTCPMax        = 639,

    Setting_Kinematics0         = 640,
    Setting_Kinematics1         = 641,
    Setting_Kinematics2         = 642,
    Setting_Kinematics3         = 643,
    Setting_Kinematics4         = 644,
    Setting_Kinematics5         = 645,
    Setting_Kinematics6         = 646,
    Setting_Kinematics7         = 647,
    Setting_Kinematics8         = 648,
    Setting_Kinematics9         = 649,

    Setting_FSOptions = 650,

    Setting_Stepper1  = 651,
    Setting_Stepper2  = 652,
    Setting_Stepper3  = 653,
    Setting_Stepper4  = 654,
    Setting_Stepper5  = 655,
    Setting_Stepper6  = 656,
    Setting_Stepper7  = 657,
    Setting_Stepper8  = 658,
    Setting_Stepper9  = 659,
    Setting_Stepper10 = 660,
    Setting_Stepper11 = 661,
    Setting_Stepper12 = 662,
    Setting_Stepper13 = 663,
    Setting_Stepper14 = 664,
    Setting_Stepper15 = 665,
    Setting_Stepper16 = 666,
    Setting_Stepper17 = 667,
    Setting_Stepper18 = 668,
    Setting_Stepper19 = 669,
    Setting_Stepper20 = 670,

    Setting_HomePinsInvertMask = 671,
    Setting_Reserved672 = 672,
    Setting_CoolantOnDelay = 673,
    Setting_THC_Options = 674,
    Setting_MacroATC_Options = 675,
    Setting_ResetActions = 676,
    Setting_StepperSpindle_Options = 677,
    Setting_RelayPortToolsetter = 678,
    Setting_RelayPortProbe2 = 679,
    Setting_StepperEnableDelay = 680,
    Setting_ModBus_StreamFormat = 681,
    Setting_THC_FeedFactor = 682,
    // 683 - 689 - reserved for Sienci

    Setting_SpindlePWMOptions1 = 709,

    Setting_SpindleInvertMask1 = 716,

    Setting_RpmMax1 = 730,
    Setting_RpmMin1 = 731,
    Setting_Mode1 = 732,
    Setting_PWMFreq1 = 733,
    Setting_PWMOffValue1 = 734,
    Setting_PWMMinValue1 = 735,
    Setting_PWMMaxValue1 = 736,

// Optional driver implemented settings for piecewise linear spindle PWM algorithm
    Setting_LinearSpindle1Piece1 = 737,
    Setting_LinearSpindle1Piece2 = 738,
    Setting_LinearSpindle1Piece3 = 739,
    Setting_LinearSpindle1Piece4 = 740,

    Setting_MotorWarningsEnable = 742,
    Setting_MotorWarningsInvert = 743,
    Setting_MotorFaultsEnable = 744,
    Setting_MotorFaultsInvert = 745,

    Setting_Action0    = 750,
    Setting_ActionBase = Setting_Action0,
    Setting_Action1    = 751,
    Setting_Action2    = 752,
    Setting_Action3    = 753,
    Setting_Action4    = 754,
    Setting_Action5    = 755,
    Setting_Action6    = 756,
    Setting_Action7    = 757,
    Setting_Action8    = 758,
    Setting_Action9    = 759,

    Setting_ActionPort0    = 760,
    Setting_ActionPortBase = Setting_ActionPort0,
    Setting_ActionPort1    = 761,
    Setting_ActionPort2    = 762,
    Setting_ActionPort3    = 763,
    Setting_ActionPort4    = 764,
    Setting_ActionPort5    = 765,
    Setting_ActionPort6    = 766,
    Setting_ActionPort7    = 767,
    Setting_ActionPort8    = 768,
    Setting_ActionPort9    = 769,

    Setting_SpindleOffsetX       = 770,
    Setting_SpindleOffsetY       = 771,
    Setting_SpindleOffsetOptions = 772,
//
// 773-779 - reserved for spindle offset settings
//

// Reserving settings in the range 800 - 899 for axis settings.
    Setting_AxisSettingsBase1 = 800,    // Reserved for driver/plugin settings
    Setting_AxisSettingsMax1 = Setting_AxisSettingsBase1 + AXIS_SETTINGS_INCREMENT * 9 + N_AXIS,
//

//
// 900-999 - reserved for automatic tool changers (ATC)
//

// ---
    Setting_SettingsMax,
    Setting_SettingsAll = Setting_SettingsMax,
// ---

    // Calculated base values for core stepper settings
    Setting_AxisStepsPerMM       = Setting_AxisSettingsBase,
    Setting_AxisMaxRate          = Setting_AxisSettingsBase + AXIS_SETTINGS_INCREMENT,
    Setting_AxisAcceleration     = Setting_AxisSettingsBase + 2 * AXIS_SETTINGS_INCREMENT,
    Setting_AxisMaxTravel        = Setting_AxisSettingsBase + 3 * AXIS_SETTINGS_INCREMENT,
    Setting_AxisStepperCurrent   = Setting_AxisSettingsBase + 4 * AXIS_SETTINGS_INCREMENT, // Not used by the core
    Setting_AxisMicroSteps       = Setting_AxisSettingsBase + 5 * AXIS_SETTINGS_INCREMENT, // Not used by the core
    Setting_AxisBacklash         = Setting_AxisSettingsBase + 6 * AXIS_SETTINGS_INCREMENT,
    Setting_AxisAutoSquareOffset = Setting_AxisSettingsBase + 7 * AXIS_SETTINGS_INCREMENT,
    Setting_AxisHomingFeedRate   = Setting_AxisSettingsBase + 8 * AXIS_SETTINGS_INCREMENT,
    Setting_AxisHomingSeekRate   = Setting_AxisSettingsBase + 9 * AXIS_SETTINGS_INCREMENT,

    Setting_AxisJerk             = Setting_AxisSettingsBase1,

    // Calculated base values for driver/plugin stepper settings
    Setting_AxisExtended0        = Setting_AxisSettingsBase2,
    Setting_AxisExtended1        = Setting_AxisSettingsBase2 + AXIS_SETTINGS_INCREMENT,
    Setting_AxisExtended2        = Setting_AxisSettingsBase2 + 2 * AXIS_SETTINGS_INCREMENT,
    Setting_AxisExtended3        = Setting_AxisSettingsBase2 + 3 * AXIS_SETTINGS_INCREMENT,
    Setting_AxisExtended4        = Setting_AxisSettingsBase2 + 4 * AXIS_SETTINGS_INCREMENT,
    Setting_AxisExtended5        = Setting_AxisSettingsBase2 + 5 * AXIS_SETTINGS_INCREMENT,
    Setting_AxisExtended6        = Setting_AxisSettingsBase2 + 6 * AXIS_SETTINGS_INCREMENT,
    Setting_AxisExtended7        = Setting_AxisSettingsBase2 + 7 * AXIS_SETTINGS_INCREMENT,
    Setting_AxisExtended8        = Setting_AxisSettingsBase2 + 8 * AXIS_SETTINGS_INCREMENT,
    Setting_AxisExtended9        = Setting_AxisSettingsBase2 + 9 * AXIS_SETTINGS_INCREMENT,

    // Calculated base values for encoder settings
    Setting_EncoderModeBase           = Setting_EncoderSettingsBase + Setting_EncoderMode,
    Setting_EncoderCPRBase            = Setting_EncoderSettingsBase + Setting_EncoderCPR,
    Setting_EncoderCPDBase            = Setting_EncoderSettingsBase + Setting_EncoderCPD,
    Setting_EncoderDblClickWindowBase = Setting_EncoderSettingsBase + Setting_EncoderDblClickWindow
} setting_id_t;

typedef enum {
    CoordinateSystem_G54 = 0,                       //!< 0 - G54 (G12)
    CoordinateSystem_G55,                           //!< 1 - G55 (G12)
    CoordinateSystem_G56,                           //!< 2 - G56 (G12)
    CoordinateSystem_G57,                           //!< 3 - G57 (G12)
    CoordinateSystem_G58,                           //!< 4 - G58 (G12)
    CoordinateSystem_G59,                           //!< 5 - G59 (G12)
#if COMPATIBILITY_LEVEL <= 1
    CoordinateSystem_G59_1,                         //!< 6 - G59.1 (G12) - availability depending on #COMPATIBILITY_LEVEL <= 1
    CoordinateSystem_G59_2,                         //!< 7 - G59.2 (G12) - availability depending on #COMPATIBILITY_LEVEL <= 1
    CoordinateSystem_G59_3,                         //!< 8 - G59.3 (G12) - availability depending on #COMPATIBILITY_LEVEL <= 1
#endif
    N_WorkCoordinateSystems,                        //!< 9 when #COMPATIBILITY_LEVEL <= 1, 6 otherwise
    CoordinateSystem_G28 = N_WorkCoordinateSystems, //!< 9 - G28 (G0) when #COMPATIBILITY_LEVEL <= 1, 6 otherwise
    CoordinateSystem_G30,                           //!< 10 - G30 (G0) when #COMPATIBILITY_LEVEL <= 1, 7 otherwise
    CoordinateSystem_G92,                           //!< 11 - G92 (G0) when #COMPATIBILITY_LEVEL <= 1, 8 otherwise
    N_CoordinateSystems                             //!< 12 when #COMPATIBILITY_LEVEL <= 1, 9 otherwise
} __attribute__ ((__packed__)) coord_system_id_t;

typedef union {
    uint8_t mask;
    uint8_t value;
    struct {
        uint8_t x :1,
                y :1,
                z :1,
                a :1,
                b :1,
                c :1,
                u :1,
                v :1;
    };
} axes_signals_t;

typedef union {
    uint8_t value;                 //!< Bitmask value
    uint8_t mask;                  //!< Synonym for bitmask value
    struct {
        uint8_t flood          :1, //!< Flood coolant.
                mist           :1, //!< Mist coolant, optional.
                shower         :1, //!< Shower coolant, currently unused.
                trough_spindle :1, //!< Through spindle coolant, currently unused.
                unused         :4;
    };
} coolant_state_t;

typedef union {
    uint8_t value;
    uint8_t mask;
    struct {
        uint8_t on               :1,
                ccw              :1,
                pwm              :1, //!< NOTE: only used for PWM inversion setting
                reserved         :1,
                override_disable :1,
                encoder_error    :1,
                at_speed         :1, //!< Spindle is at speed.
                synchronized     :1;
    };
} spindle_state_t;

// NOTE: the pin_function_t enum must be kept in sync with any changes!
typedef union {
    uint16_t bits;
    uint16_t mask;
    uint16_t value;
    struct {
        uint16_t reset                :1,
                 feed_hold            :1,
                 cycle_start          :1,
                 safety_door_ajar     :1,
                 block_delete         :1,
                 stop_disable         :1, //! M1
                 e_stop               :1,
                 probe_disconnected   :1,
                 motor_fault          :1,
                 motor_warning        :1,
                 limits_override      :1,
                 single_block         :1,
                 tls_overtravel       :1, //! used for probe (toolsetter) protection
                 probe_overtravel     :1, //! used for probe protection
                 probe_triggered      :1, //! used for probe protection
                 deasserted           :1; //! this flag is set if signals are deasserted.
    };
} control_signals_t;

typedef uint_fast16_t override_t;

typedef struct {
    override_t feed_rate;           //!< Feed rate override value in percent
    override_t rapid_rate;          //!< Rapids override value in percent
    override_t spindle_rpm;         //!< __NOTE:_ Not used by the core, it maintain per spindle override in \ref spindle_param_t
//    spindle_stop_t spindle_stop;    //!< Tracks spindle stop override states
//    gc_override_flags_t control;    //!< Tracks override control states.
} overrides_t;

#endif
