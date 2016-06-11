#ifndef __S1AP_PROTO_IES_H__
#define __S1AP_PROTO_IES_H__

#include <stdint.h>
#include "../pdu.h"

typedef void (*s1ap_pie_func)(pdu_node_t *node, char *data, uint16_t size);
typedef struct s1ap_pie_s {
    uint16_t        id;
    char           *name;
    s1ap_pie_func   func;
} s1ap_pie_t;

void pie_0_MME_UE_ID    (pdu_node_t *node, char *data, uint16_t size);
void pie_1_HandoverType (pdu_node_t *node, char *data, uint16_t size);
void pie_2_Cause        (pdu_node_t *node, char *data, uint16_t size);
void pie_3_SourceID     (pdu_node_t *node, char *data, uint16_t size);
void pie_4_TargetID     (pdu_node_t *node, char *data, uint16_t size);
/*   pie_5:  unknown */
/*   pie_6:  unknown */
/*   pie_7:  unknown */
void pie_8_ENB_UE_ID    (pdu_node_t *node, char *data, uint16_t size);
/*   pie_9:  unknown */
/*   pie_10: unknown */
/*   pie_11: unknown */
void pie_12_ERABSubjecttoDataForwardingList (pdu_node_t *node, char *data, uint16_t size);
void pie_13_ERABtoReleaseListHOCmd          (pdu_node_t *node, char *data, uint16_t size);
void pie_14_ERABDataForwardingItem          (pdu_node_t *node, char *data, uint16_t size);
void pie_15_ERABReleaseItemBearerRelComp    (pdu_node_t *node, char *data, uint16_t size);
void pie_16_ERABToBeSetupListBearerSUReq    (pdu_node_t *node, char *data, uint16_t size);
void pie_17_ERABToBeSetupItemBearerSUReq    (pdu_node_t *node, char *data, uint16_t size);
void pie_18_ERABAdmittedList                (pdu_node_t *node, char *data, uint16_t size);
void pie_19_ERABFailedToSetupListHOReqAck   (pdu_node_t *node, char *data, uint16_t size);
void pie_20_RABAdmittedItem                 (pdu_node_t *node, char *data, uint16_t size);
void pie_21_ERABFailedtoSetupItemHOReqAck   (pdu_node_t *node, char *data, uint16_t size);
void pie_22_ERABToBeSwitchedDLList          (pdu_node_t *node, char *data, uint16_t size);
void pie_23_ERABToBeSwitchedDLItem          (pdu_node_t *node, char *data, uint16_t size);
void pie_24_ERABToBeSetupListCtxtSUReq      (pdu_node_t *node, char *data, uint16_t size);
void pie_25_TraceActivation                 (pdu_node_t *node, char *data, uint16_t size);
void pie_26_NAS_PDU                         (pdu_node_t *node, char *data, uint16_t size);
void pie_27_ERABToBeSetupItemHOReq          (pdu_node_t *node, char *data, uint16_t size);
void pie_28_ERABSetupListBearerSURes        (pdu_node_t *node, char *data, uint16_t size);
void pie_29_ERABFailedToSetupListBearerSURes(pdu_node_t *node, char *data, uint16_t size);
void pie_30_ERABToBeModifiedListBearerModReq(pdu_node_t *node, char *data, uint16_t size);
void pie_31_ERABModifyListBearerModRes      (pdu_node_t *node, char *data, uint16_t size);
void pie_32_ERABFailedToModifyList          (pdu_node_t *node, char *data, uint16_t size);
void pie_33_ERABToBeReleasedList            (pdu_node_t *node, char *data, uint16_t size);
void pie_34_ERABFailedToReleaseList         (pdu_node_t *node, char *data, uint16_t size);
void pie_35_ERABItem                        (pdu_node_t *node, char *data, uint16_t size);
void pie_36_ERABToBeModifiedItemBearerModReq(pdu_node_t *node, char *data, uint16_t size);
void pie_37_ERABModifyItemBearerModRes      (pdu_node_t *node, char *data, uint16_t size);
void pie_38_ERABReleaseItem                 (pdu_node_t *node, char *data, uint16_t size);
void pie_39_ERABSetupItemBearerSURes        (pdu_node_t *node, char *data, uint16_t size);



void pie_40_SecurityContext                 (pdu_node_t *node, char *data, uint16_t size);
void pie_41_HandoverRestrictionList         (pdu_node_t *node, char *data, uint16_t size);
/*   pie_42: unknown */
void pie_43_UEPagingID                      (pdu_node_t *node, char *data, uint16_t size);
void pie_44_pagingDRX                       (pdu_node_t *node, char *data, uint16_t size);
/*   pie_45: unknown */
void pie_46_TAIList                         (pdu_node_t *node, char *data, uint16_t size);
void pie_47_TAIItem                         (pdu_node_t *node, char *data, uint16_t size);
void pie_48_ERABFailedToSetupListCtxtSURes  (pdu_node_t *node, char *data, uint16_t size);
void pie_49_ERABReleaseItemHOCmd            (pdu_node_t *node, char *data, uint16_t size);
void pie_50_ERABSetupItemCtxtSURes          (pdu_node_t *node, char *data, uint16_t size);
void pie_51_ERABSetupListCtxtSURes          (pdu_node_t *node, char *data, uint16_t size);
void pie_52_ERABToBeSetupItemCtxtSUReq      (pdu_node_t *node, char *data, uint16_t size);
void pie_53_ERABToBeSetupListHOReq          (pdu_node_t *node, char *data, uint16_t size);
/*   pie_54: unknown */
void pie_55_GERANtoLTEHOInformationRes      (pdu_node_t *node, char *data, uint16_t size);
/*   pie_56: unknown */
void pie_57_UTRANtoLTEHOInformationRes      (pdu_node_t *node, char *data, uint16_t size);
void pie_58_CriticalityDiagnostics          (pdu_node_t *node, char *data, uint16_t size);
void pie_59_Global_ENB_ID                   (pdu_node_t *node, char *data, uint16_t size);
void pie_60_eNBname                         (pdu_node_t *node, char *data, uint16_t size);
void pie_61_MMEname                         (pdu_node_t *node, char *data, uint16_t size);
/*   pie_62: unknown */
void pie_63_ServedPLMNs                     (pdu_node_t *node, char *data, uint16_t size);
void pie_64_SupportedTAs                    (pdu_node_t *node, char *data, uint16_t size);
void pie_65_TimeToWait                      (pdu_node_t *node, char *data, uint16_t size);
void pie_66_UEAggregateMaximumBitrate       (pdu_node_t *node, char *data, uint16_t size);
void pie_67_TAI                             (pdu_node_t *node, char *data, uint16_t size);
void pie_69_ERABReleaseListBearerRelComp    (pdu_node_t *node, char *data, uint16_t size);
void pie_70_cdma2000PDU                     (pdu_node_t *node, char *data, uint16_t size);
void pie_71_cdma2000RATType                 (pdu_node_t *node, char *data, uint16_t size);
void pie_72_cdma2000SectorID                (pdu_node_t *node, char *data, uint16_t size);
void pie_73_SecurityKey                     (pdu_node_t *node, char *data, uint16_t size);
void pie_74_UERadioCapability               (pdu_node_t *node, char *data, uint16_t size);
void pie_75_GUMMEI_ID                       (pdu_node_t *node, char *data, uint16_t size);
/*   pie_76: unknown */
/*   pie_77: unknown */
void pie_78_ERABInformationListItem         (pdu_node_t *node, char *data, uint16_t size);
void pie_79_DirectForwardingPathAvailability(pdu_node_t *node, char *data, uint16_t size);



void pie_80_UEIdentityIndexValue            (pdu_node_t *node, char *data, uint16_t size);
/*   pie_81: unknown */
/*   pie_82: unknown */
void pie_83_cdma2000HOStatus                (pdu_node_t *node, char *data, uint16_t size);
void pie_84_cdma2000HORequiredIndication    (pdu_node_t *node, char *data, uint16_t size);
void pie_86_EUTRANTraceID                   (pdu_node_t *node, char *data, uint16_t size);
void pie_87_RelativeMMECapacity             (pdu_node_t *node, char *data, uint16_t size);
void pie_88_SourceMME_UE_S1AP_ID            (pdu_node_t *node, char *data, uint16_t size);
void pie_89_BearersSubjectToStatusTransferItem(pdu_node_t *node, char *data, uint16_t size);
void pie_90_eNB_StatusTransferTransparentContainer(pdu_node_t *node, char *data, uint16_t size);
void pie_91_UE_associatedLogicalS1ConnectionItem(pdu_node_t *node, char *data, uint16_t size);
void pie_92_ResetType                       (pdu_node_t *node, char *data, uint16_t size);
void pie_93_UE_associatedLogicalS1ConnectionListResAck(pdu_node_t *node, char *data, uint16_t size);
void pie_94_ERABToBeSwitchedULItem          (pdu_node_t *node, char *data, uint16_t size);
void pie_95_ERABToBeSwitchedULList          (pdu_node_t *node, char *data, uint16_t size);
void pie_96_STMSI                           (pdu_node_t *node, char *data, uint16_t size);
void pie_97_cdma2000OneXRAND                (pdu_node_t *node, char *data, uint16_t size);
void pie_98_RequestType                     (pdu_node_t *node, char *data, uint16_t size);
void pie_99_UE_S1AP_IDs                     (pdu_node_t *node, char *data, uint16_t size);
void pie_100_EUTRAN_CGI                     (pdu_node_t *node, char *data, uint16_t size);
void pie_101_OverloadResponse               (pdu_node_t *node, char *data, uint16_t size);
void pie_102_cdma2000OneXSRVCCInfo          (pdu_node_t *node, char *data, uint16_t size);
void pie_103_ERABFailedToBeReleasedList     (pdu_node_t *node, char *data, uint16_t size);
void pie_104_SourceToTargetTransparentContainer(pdu_node_t *node, char *data, uint16_t size);
void pie_105_ServedGUMMEIs                  (pdu_node_t *node, char *data, uint16_t size);
void pie_106_SubscriberProfileIDforRFP      (pdu_node_t *node, char *data, uint16_t size);
void pie_107_UESecurityCapabilities         (pdu_node_t *node, char *data, uint16_t size);
void pie_108_CSFallbackIndicator            (pdu_node_t *node, char *data, uint16_t size);
void pie_109_CNDomain                       (pdu_node_t *node, char *data, uint16_t size);
void pie_110_ERABReleasedList               (pdu_node_t *node, char *data, uint16_t size);
void pie_111_MessageIdentifier              (pdu_node_t *node, char *data, uint16_t size);
void pie_112_SerialNumber                   (pdu_node_t *node, char *data, uint16_t size);
void pie_113_WarningAreaList                (pdu_node_t *node, char *data, uint16_t size);
void pie_114_RepetitionPeriod               (pdu_node_t *node, char *data, uint16_t size);
void pie_115_NumberofBroadcastRequest       (pdu_node_t *node, char *data, uint16_t size);
void pie_116_WarningType                    (pdu_node_t *node, char *data, uint16_t size);
void pie_117_WarningSecurityInfo            (pdu_node_t *node, char *data, uint16_t size);
void pie_118_DataCodingScheme               (pdu_node_t *node, char *data, uint16_t size);
void pie_119_WarningMessageContents         (pdu_node_t *node, char *data, uint16_t size);



void pie_120_BroadcastCompletedAreaList     (pdu_node_t *node, char *data, uint16_t size);
void pie_121_InterSystemInformationTransferTypeEDT(pdu_node_t *node, char *data, uint16_t size);
void pie_122_InterSystemInformationTransferTypeMDT(pdu_node_t *node, char *data, uint16_t size);
void pie_123_TargetToSourceTransparentContainer(pdu_node_t *node, char *data, uint16_t size);
void pie_124_SRVCCOperationPossible         (pdu_node_t *node, char *data, uint16_t size);
void pie_125_SRVCCHOIndication              (pdu_node_t *node, char *data, uint16_t size);
void pie_126_NASDownlinkCount               (pdu_node_t *node, char *data, uint16_t size);
void pie_127_CSGId                          (pdu_node_t *node, char *data, uint16_t size);
void pie_128_CSGIdList                      (pdu_node_t *node, char *data, uint16_t size);
void pie_129_SONConfigurationTransferECT    (pdu_node_t *node, char *data, uint16_t size);
void pie_130_SONConfigurationTransferMCT    (pdu_node_t *node, char *data, uint16_t size);
void pie_131_TraceCollectionEntityIPAddress (pdu_node_t *node, char *data, uint16_t size);
void pie_132_MSClassmark2                   (pdu_node_t *node, char *data, uint16_t size);
void pie_133_MSClassmark3                   (pdu_node_t *node, char *data, uint16_t size);
void pie_134_RRCEstablishmentCause          (pdu_node_t *node, char *data, uint16_t size);
void pie_135_NASSecurityParametersFromEUTRAN(pdu_node_t *node, char *data, uint16_t size);
void pie_136_NASSecurityParametersToEUTRAN  (pdu_node_t *node, char *data, uint16_t size);
void pie_137_DefaultPagingDRX               (pdu_node_t *node, char *data, uint16_t size);
void pie_138_SourceToTargetTransparentContainerSecondary(pdu_node_t *node, char *data, uint16_t size);
void pie_139_TargetToSourceTransparentContainerSecondary(pdu_node_t *node, char *data, uint16_t size);
void pie_140_EUTRANRoundTripDelayEstimationInfo(pdu_node_t *node, char *data, uint16_t size);
void pie_141_BroadcastCancelledAreaList     (pdu_node_t *node, char *data, uint16_t size);
void pie_142_ConcurrentWarningMessageIndicator(pdu_node_t *node, char *data, uint16_t size);
void pie_143_DataForwardingNotPossible      (pdu_node_t *node, char *data, uint16_t size);
void pie_144_ExtendedRepetitionPeriod       (pdu_node_t *node, char *data, uint16_t size);
void pie_145_CellAccessMode                 (pdu_node_t *node, char *data, uint16_t size);
void pie_146_CSGMembershipStatus            (pdu_node_t *node, char *data, uint16_t size);
void pie_147_LPPaPDU                        (pdu_node_t *node, char *data, uint16_t size);
void pie_148_RoutingID                      (pdu_node_t *node, char *data, uint16_t size);
void pie_149_TimeSynchronizationInfo        (pdu_node_t *node, char *data, uint16_t size);
void pie_150_PSServiceNotAvailable          (pdu_node_t *node, char *data, uint16_t size);
void pie_151_PagingPriority                 (pdu_node_t *node, char *data, uint16_t size);
void pie_152_x2TNLConfigurationInfo         (pdu_node_t *node, char *data, uint16_t size);
void pie_153_eNBX2ExtendedTransportLayerAddresses(pdu_node_t *node, char *data, uint16_t size);
void pie_154_GUMMEIList                     (pdu_node_t *node, char *data, uint16_t size);
void pie_155_GWTransportLayerAddress        (pdu_node_t *node, char *data, uint16_t size);
void pie_156_CorrelationID                  (pdu_node_t *node, char *data, uint16_t size);
void pie_157_SourceMME_GUMMEI               (pdu_node_t *node, char *data, uint16_t size);
void pie_158_MME_UE_S1AP_ID_2               (pdu_node_t *node, char *data, uint16_t size);
void pie_159_RegisteredLAI                  (pdu_node_t *node, char *data, uint16_t size);
void pie_160_RelayNode_Indicator            (pdu_node_t *node, char *data, uint16_t size);
void pie_161_TrafficLoadReductionIndication (pdu_node_t *node, char *data, uint16_t size);
void pie_162_MDTConfiguration               (pdu_node_t *node, char *data, uint16_t size);
void pie_163_MMERelaySupportIndicator       (pdu_node_t *node, char *data, uint16_t size);
void pie_164_GWContextReleaseIndication     (pdu_node_t *node, char *data, uint16_t size);
void pie_165_ManagementBasedMDTAllowed      (pdu_node_t *node, char *data, uint16_t size);

#endif
