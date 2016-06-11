#include "../pdu.h"
#include "s1ap_dict.h"


struct dict_node
dict_nodes[] = {
    {"S1AP",                "S1 Application Protocol", DICT_NTYPE_PROTO,   DICT_DTYPE_BYTES, true, NULL, NULL},
    {"S1AP-PDU",            "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"initiatingMessage",   "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"successfulOutcome",   "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"unsuccessfulOutcome", "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"Item",                "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

    {"pduType",             "",                        DICT_NTYPE_BITSET,  DICT_DTYPE_UINT8, false,NULL, NULL},
    {"procedureCode",       "",                        DICT_NTYPE_FIELD,   DICT_DTYPE_UINT8, true, NULL, NULL},
    {"critically",          "",                        DICT_NTYPE_BITSET,  DICT_DTYPE_UINT16,true, NULL, NULL},
    {"valueSize",           "",                        DICT_NTYPE_BITSET,  DICT_DTYPE_UINT16,true, NULL, NULL},

    {"value",               "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

    {"Paging",              "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"uplinkNASTransport",  "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"initialUEMessage",    "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"UEContextRelease",    "",                        DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"UEContextModificationRequest", "",               DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

    {"protocolIEs",               "",                  DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"protocolIE-field",          "",                  DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"protocolIE-SingleContainer","",                  DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

    {"id",                     "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT16,true, NULL, NULL},

        /* ---- */
    {"MME-UE-S1AP-ID",         "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT24,true, NULL, NULL},
    {"ENB-UE-S1AP-ID",         "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT16,true, NULL, NULL},

        /* 2  */
    {"Cause",                  "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"radioNetwork",           "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT8, true, NULL, NULL},

        /* 43 */
    {"UEPagingID",             "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"s-TMSI",                 "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"mMEC",                   "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_HEX16, true, NULL, NULL},
    {"m-TMSI",                 "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_HEX32, true, NULL, NULL},

        /* 46 */
    {"TAIList",                "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

        /* 47 */
    {"TAIItem",                "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"pLMNIdentity",           "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_HEX24, true, NULL, NULL},
    {"tAC",                    "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_HEX16, true, NULL, NULL},
    {"MCC",                    "",                     DICT_NTYPE_BITSET,  DICT_DTYPE_HEX16, true, NULL, NULL},
    {"MNC",                    "",                     DICT_NTYPE_BITSET,  DICT_DTYPE_HEX16, true, NULL, NULL},

        /* 66 */
    {"UEAggregateMaximumBitrate","",                   DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"uEaggregateMaximumBitRateDL","",                 DICT_NTYPE_FIELD,   DICT_DTYPE_UINT32, true, NULL, NULL},
    {"uEaggregateMaximumBitRateUL","",                 DICT_NTYPE_FIELD,   DICT_DTYPE_UINT32, true, NULL, NULL},

        /* 67 */
    {"TAI",                    "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

        /* 80 */
    {"UEIdentityIndexValue",   "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_HEX16, true, NULL, NULL},

        /* 99 */
    {"UE_S1AP_IDs",            "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"uE-S1AP-ID-pair",        "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},

        /* 100 */
    {"EUTRAN-CGI",             "",                     DICT_NTYPE_SECTION, DICT_DTYPE_BYTES, true, NULL, NULL},
    {"cell-ID",                "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_HEX32, true, NULL, NULL},

        /* 109 */
    {"CNDomain",               "",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT8, true, NULL, NULL},

        /* 134 */
    {"RRC-Establishment-Cause","",                     DICT_NTYPE_FIELD,   DICT_DTYPE_UINT8, true, NULL, NULL},

    {NULL,                  NULL,                      0,                  0,                true, NULL, NULL}
};


s1ap_pie_t s1ap_pies[] = {
    {  0, "MME-UE-S1AP-ID",                  pie_0_MME_UE_ID },
    {  1, "HandoverType",                    pie_1_HandoverType },
    {  2, "Cause",                           pie_2_Cause },
    {  3, "SourceID",                        pie_3_SourceID },
    {  4, "TargetID",                        pie_4_TargetID },
    {  5, NULL,                              NULL },
    {  6, NULL,                              NULL },
    {  7, NULL,                              NULL },
    {  8, "ENB-UE-S1AP-ID",                  pie_8_ENB_UE_ID },
    {  9, NULL,                              NULL },
    { 10, NULL,                              NULL },
    { 11, NULL,                              NULL },
    { 12, "E-RABSubjecttoDataForwardingList",pie_12_ERABSubjecttoDataForwardingList },
    { 13, "E-RABtoReleaseListHOCmd",         pie_13_ERABtoReleaseListHOCmd },
    { 14, "E-RABDataForwardingItem",         pie_14_ERABDataForwardingItem },
    { 15, "E-RABReleaseItemBearerRelComp",   pie_15_ERABReleaseItemBearerRelComp },
    { 16, "E-RABToBeSetupListBearerSUReq",   pie_16_ERABToBeSetupListBearerSUReq },
    { 17, "E-RABToBeSetupItemBearerSUReq",   pie_17_ERABToBeSetupItemBearerSUReq },
    { 18, "E-RABAdmittedList",               pie_18_ERABAdmittedList },
    { 19, "E-RABFailedToSetupListHOReqAck",  pie_19_ERABFailedToSetupListHOReqAck },
    { 20, "RABAdmittedItem",                 pie_20_RABAdmittedItem },
    { 21, "E-RABFailedtoSetupItemHOReqAck",  pie_21_ERABFailedtoSetupItemHOReqAck },
    { 22, "E-RABToBeSwitchedDLList",         pie_22_ERABToBeSwitchedDLList },
    { 23, "E-RABToBeSwitchedDLItem",         pie_23_ERABToBeSwitchedDLItem },
    { 24, "E-RABToBeSetupListCtxtSUReq",     pie_24_ERABToBeSetupListCtxtSUReq },
    { 25, "TraceActivation",                 pie_25_TraceActivation },
    { 26, "NAS-PDU",                         pie_26_NAS_PDU },
    { 27, "E-RABToBeSetupItemHOReq",         pie_27_ERABToBeSetupItemHOReq },
    { 28, "E-RABSetupListBearerSURes",       pie_28_ERABSetupListBearerSURes },
    { 29, "E-RABFailedToSetupListBearerSURes", pie_29_ERABFailedToSetupListBearerSURes },
    { 30, "E-RABToBeModifiedListBearerModReq", pie_30_ERABToBeModifiedListBearerModReq },
    { 31, "E-RABModifyListBearerModRes",     pie_31_ERABModifyListBearerModRes },
    { 32, "E-RABFailedToModifyList",         pie_32_ERABFailedToModifyList },
    { 33, "E-RABToBeReleasedList",           pie_33_ERABToBeReleasedList },
    { 34, "E-RABFailedToReleaseList",        pie_34_ERABFailedToReleaseList },
    { 35, "E-RABItem",                       pie_35_ERABItem },
    { 36, "E-RABToBeModifiedItemBearerModReq", pie_36_ERABToBeModifiedItemBearerModReq },
    { 37, "E-RABModifyItemBearerModRes",     pie_37_ERABModifyItemBearerModRes },
    { 38, "E-RABReleaseItem",                pie_38_ERABReleaseItem },
    { 39, "E-RABSetupItemBearerSURes",       pie_39_ERABSetupItemBearerSURes },


    { 40, "SecurityContext",                 pie_40_SecurityContext },
    { 41, "HandoverRestrictionList",         pie_41_HandoverRestrictionList },
    { 42, NULL,                              NULL },
    { 43, "UEPagingID",                      pie_43_UEPagingID },
    { 44, "pagingDRX",                       pie_44_pagingDRX },
    { 45, NULL,                              NULL },
    { 46, "TAIList",                         pie_46_TAIList },
    { 47, "TAIItem",                         pie_47_TAIItem },
    { 48, "E-RABFailedToSetupListCtxtSURes", pie_48_ERABFailedToSetupListCtxtSURes },
    { 49, "E-RABReleaseItemHOCmd",           pie_49_ERABReleaseItemHOCmd },
    { 50, "E-RABSetupItemCtxtSURes",         pie_50_ERABSetupItemCtxtSURes },
    { 51, "E-RABSetupListCtxtSURes",         pie_51_ERABSetupListCtxtSURes },
    { 52, "E-RABToBeSetupItemCtxtSUReq",     pie_52_ERABToBeSetupItemCtxtSUReq },
    { 53, "E-RABToBeSetupListHOReq",         pie_53_ERABToBeSetupListHOReq },
    { 54, NULL,                              NULL },
    { 55, "GERANtoLTEHOInformationRes",      pie_55_GERANtoLTEHOInformationRes },
    { 56, NULL,                              NULL },
    { 57, "E-RABSubjecttoDataForwardingList",pie_57_UTRANtoLTEHOInformationRes },
    { 58, "UTRANtoLTEHOInformationRes",      pie_58_CriticalityDiagnostics },
    { 59, "Global_ENB_ID",                   pie_59_Global_ENB_ID },
    { 60, "eNBname",                         pie_60_eNBname },
    { 61, "MMEname",                         pie_61_MMEname },
    { 62, NULL,                              NULL },
    { 63, "ServedPLMNs",                     pie_63_ServedPLMNs },
    { 64, "SupportedTAs",                    pie_64_SupportedTAs },
    { 65, "TimeToWait",                      pie_65_TimeToWait },
    { 66, "UEAggregateMaximumBitrate",       pie_66_UEAggregateMaximumBitrate },
    { 67, "TAI",                             pie_67_TAI },
    { 68, NULL,                              NULL },
    { 69, "E-RABReleaseListBearerRelComp",   pie_69_ERABReleaseListBearerRelComp },
    { 70, "cdma2000PDU",                     pie_70_cdma2000PDU },
    { 71, "cdma2000RATType",                 pie_71_cdma2000RATType },
    { 72, "cdma2000SectorID",                pie_72_cdma2000SectorID },
    { 73, "SecurityKey",                     pie_73_SecurityKey },
    { 74, "UERadioCapability",               pie_74_UERadioCapability },
    { 75, "GUMMEI_ID",                       pie_75_GUMMEI_ID },
    { 76, NULL,                              NULL },
    { 77, NULL,                              NULL },
    { 78, "E-RABInformationListItem",        pie_78_ERABInformationListItem },
    { 79, "DirectForwardingPathAvailability",pie_79_DirectForwardingPathAvailability },


    {  80, "UEIdentityIndexValue",            pie_80_UEIdentityIndexValue },
    {  81, NULL,                              NULL },
    {  82, NULL,                              NULL },
    {  83, "cdma2000HOStatus",                pie_83_cdma2000HOStatus },
    {  84, "cdma2000HORequiredIndication",    pie_84_cdma2000HORequiredIndication },
    {  85, NULL,                              NULL },
    {  86, "EUTRANTraceID",                   pie_86_EUTRANTraceID },
    {  87, "RelativeMMECapacity",             pie_87_RelativeMMECapacity },
    {  88, "SourceMME_UE_S1AP_ID",            pie_88_SourceMME_UE_S1AP_ID },
    {  89, "BearersSubjectToStatusTransferItem",         pie_89_BearersSubjectToStatusTransferItem },
    {  90, "eNB_StatusTransferTransparentContainer",     pie_90_eNB_StatusTransferTransparentContainer },
    {  91, "UE-associatedLogicalS1ConnectionItem",       pie_91_UE_associatedLogicalS1ConnectionItem },
    {  92, "ResetType",                                  pie_92_ResetType },
    {  93, "UE-associatedLogicalS1ConnectionListResAck", pie_93_UE_associatedLogicalS1ConnectionListResAck },
    {  94, "E-RABToBeSwitchedULItem",         pie_94_ERABToBeSwitchedULItem },
    {  95, "E-RABToBeSwitchedULList",         pie_95_ERABToBeSwitchedULList },
    {  96, "STMSI",                           pie_96_STMSI },
    {  97, "cdma2000OneXRAND",                pie_97_cdma2000OneXRAND },
    {  98, "RequestType",                     pie_98_RequestType },
    {  99, "UE-S1AP-IDs",                     pie_99_UE_S1AP_IDs },
    { 100, "EUTRAN-CGI",                      pie_100_EUTRAN_CGI },
    { 101, "OverloadResponse",                pie_101_OverloadResponse },
    { 102, "cdma2000OneXSRVCCInfo",           pie_102_cdma2000OneXSRVCCInfo },
    { 103, "E-RABFailedToBeReleasedList",     pie_103_ERABFailedToBeReleasedList },
    { 104, "SourceToTargetTransparentContainer", pie_104_SourceToTargetTransparentContainer },
    { 105, "ServedGUMMEIs",                   pie_105_ServedGUMMEIs },
    { 106, "SubscriberProfileIDforRFP",       pie_106_SubscriberProfileIDforRFP },
    { 107, "UESecurityCapabilities",          pie_107_UESecurityCapabilities },
    { 108, "CSFallbackIndicator",             pie_108_CSFallbackIndicator },
    { 109, "CNDomain",                        pie_109_CNDomain },
    { 110, "E-RABReleasedList",               pie_110_ERABReleasedList },
    { 111, "MessageIdentifier",               pie_111_MessageIdentifier },
    { 112, "SerialNumber",                    pie_112_SerialNumber },
    { 113, "WarningAreaList",                 pie_113_WarningAreaList },
    { 114, "RepetitionPeriod",                pie_114_RepetitionPeriod },
    { 115, "NumberofBroadcastRequest",        pie_115_NumberofBroadcastRequest },
    { 116, "WarningType",                     pie_116_WarningType },
    { 117, "WarningSecurityInfo",             pie_117_WarningSecurityInfo },
    { 118, "DataCodingScheme",                pie_118_DataCodingScheme },
    { 119, "WarningMessageContents",          pie_119_WarningMessageContents },


    { 120, "BroadcastCompletedAreaList",            pie_120_BroadcastCompletedAreaList },
    { 121, "InterSystemInformationTransferTypeEDT", pie_121_InterSystemInformationTransferTypeEDT },
    { 122, "InterSystemInformationTransferTypeMDT", pie_122_InterSystemInformationTransferTypeMDT },
    { 123, "TargetToSourceTransparentContainer",    pie_123_TargetToSourceTransparentContainer },
    { 124, "SRVCCOperationPossible",          pie_124_SRVCCOperationPossible },
    { 125, "SRVCCHOIndication",               pie_125_SRVCCHOIndication },
    { 126, "NASDownlinkCount",                pie_126_NASDownlinkCount },
    { 127, "CSGId",                           pie_127_CSGId },
    { 128, "CSGIdList",                       pie_128_CSGIdList },
    { 129, "SONConfigurationTransferECT",     pie_129_SONConfigurationTransferECT },
    { 130, "SONConfigurationTransferMCT",     pie_130_SONConfigurationTransferMCT },
    { 131, "TraceCollectionEntityIPAddress",  pie_131_TraceCollectionEntityIPAddress },
    { 132, "MSClassmark2",                    pie_132_MSClassmark2 },
    { 133, "MSClassmark3",                    pie_133_MSClassmark3 },
    { 134, "RRCEstablishmentCause",           pie_134_RRCEstablishmentCause },
    { 135, "NASSecurityParametersFromEUTRAN", pie_135_NASSecurityParametersFromEUTRAN },
    { 136, "NASSecurityParametersToEUTRAN",   pie_136_NASSecurityParametersToEUTRAN },
    { 137, "DefaultPagingDRX",                pie_137_DefaultPagingDRX },
    { 138, "SourceToTargetTransparentContainerSecondary", pie_138_SourceToTargetTransparentContainerSecondary },
    { 139, "TargetToSourceTransparentContainerSecondary", pie_139_TargetToSourceTransparentContainerSecondary },
    { 140, "EUTRANRoundTripDelayEstimationInfo", pie_140_EUTRANRoundTripDelayEstimationInfo },
    { 141, "BroadcastCancelledAreaList",         pie_141_BroadcastCancelledAreaList },
    { 142, "ConcurrentWarningMessageIndicator",  pie_142_ConcurrentWarningMessageIndicator },
    { 143, "DataForwardingNotPossible",       pie_143_DataForwardingNotPossible },
    { 144, "ExtendedRepetitionPeriod",        pie_144_ExtendedRepetitionPeriod },
    { 145, "CellAccessMode",                  pie_145_CellAccessMode },
    { 146, "CSGMembershipStatus",             pie_146_CSGMembershipStatus },
    { 147, "LPPaPDU",                         pie_147_LPPaPDU },
    { 148, "RoutingID",                       pie_148_RoutingID },
    { 149, "TimeSynchronizationInfo",         pie_149_TimeSynchronizationInfo },
    { 150, "PSServiceNotAvailable",           pie_150_PSServiceNotAvailable },
    { 151, "PagingPriority",                  pie_151_PagingPriority },
    { 152, "x2TNLConfigurationInfo",          pie_152_x2TNLConfigurationInfo },
    { 153, "eNBX2ExtendedTransportLayerAddresses", pie_153_eNBX2ExtendedTransportLayerAddresses },
    { 154, "E-RABGUMMEIList",                 pie_154_GUMMEIList },
    { 155, "GWTransportLayerAddress",         pie_155_GWTransportLayerAddress },
    { 156, "CorrelationID",                   pie_156_CorrelationID },
    { 157, "SourceMME_GUMMEI",                pie_157_SourceMME_GUMMEI },
    { 158, "MME-UE-S1AP-ID-2",                pie_158_MME_UE_S1AP_ID_2 },
    { 159, "RegisteredLAI",                   pie_159_RegisteredLAI },


    { 160, "RelayNode-Indicator",             pie_160_RelayNode_Indicator },
    { 161, "TrafficLoadReductionIndication",  pie_161_TrafficLoadReductionIndication },
    { 162, "MDTConfiguration",                pie_162_MDTConfiguration },
    { 163, "MMERelaySupportIndicator",        pie_163_MMERelaySupportIndicator },
    { 164, "GWContextReleaseIndication",      pie_164_GWContextReleaseIndication },
    { 165, "ManagementBasedMDTAllowed",       pie_165_ManagementBasedMDTAllowed },
};
const size_t s1ap_pies_sz = sizeof(s1ap_pies) / sizeof(s1ap_pies[0]);

s1ap_proccode_t s1ap_proccodes[] = {
    { 0, "HandoverPreparation"},
    { 1, "HandoverResourceAllocation"},
    { 2, "HandoverNotification"},
    { 3, "PathSwitchRequest"},
    { 4, "HandoverCancel"},
    { 5, "E-RABSetup"},
    { 6, "E-RABModify"},
    { 7, "E-RABRelease"},
    { 8, "E-RABReleaseIndication"},
    { 9, "InitialContextSetup"},
    {10, "Paging"},
    {11, "downlinkNASTransport"},
    {12, "initialUEMessage"},
    {13, "uplinkNASTransport"},
    {14, "Reset"},
    {15, "ErrorIndication"},
    {16, "NASNonDeliveryIndication"},
    {17, "S1Setup"},
    {18, "UEContextReleaseRequest"},
    {19, "DownlinkS1cdma2000tunneling"},
    {20, "UplinkS1cdma2000tunneling"},
    {21, "UEContextModification"},
    {22, "UECapabilityInfoIndication"},
    {23, "UEContextRelease"},
    {24, "eNBStatusTransfer"},
    {25, "MMEStatusTransfer"},
    {26, "DeactivateTrace"},
    {27, "TraceStart"},
    {28, "TraceFailureIndication"},
    {29, "ENBConfigurationUpdate"},
    {30, "MMEConfigurationUpdate"},
    {31, "LocationReportingControl"},
    {32, "LocationReportingFailureIndication"},
    {33, "LocationReport"},
    {34, "OverloadStart"},
    {35, "OverloadStop"},
    {36, "WriteReplaceWarning"},
    {37, "eNBDirectInformationTransfer"},
    {38, "MMEDirectInformationTransfer"},
    {39, "PrivateMessage"},
    {40, "eNBConfigurationTransfer"},
    {41, "MMEConfigurationTransfer"},
    {42, "CellTrafficTrace"},
    {43, "Kill"},
    {44, "downlinkUEAssociatedLPPaTransport"},
    {45, "uplinkUEAssociatedLPPaTransport"},
    {46, "downlinkNonUEAssociatedLPPaTransport"},
    {47, "uplinkNonUEAssociatedLPPaTransport"}
};
const size_t s1ap_proccodes_sz = sizeof(s1ap_proccodes) / sizeof(s1ap_proccodes[0]);
