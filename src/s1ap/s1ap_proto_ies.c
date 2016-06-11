#include <byteswap.h>

#include "s1ap.h"
#include "s1ap_dict.h"
#include "s1ap_proto_ies.h"


#pragma pack(push, 1)

struct s1ap_43_UEPagingID {
    uint8_t mmec;
    uint8_t mmec_;
    uint32_t mtmsi;
};

struct s1ap_47_TAIItem {
    uint8_t  padding;
    uint8_t  PLMNId[3];
    uint16_t tAC;
};

struct s1ap_66_UEAggregateMaximumBitrate {
    uint8_t   padding0;
    uint32_t  uEaggregateMaximumBitRateDL;
    uint8_t   padding1;
    uint32_t  uEaggregateMaximumBitRateUL;
};

struct s1ap_67_TAI {
    uint8_t  padding;
    uint8_t  PLMNId[3];
    uint16_t tAC;
};

struct s1ap_99_UE_S1AP_IDs {
    uint8_t   padding0;
    uint32_t  mMe;
    uint8_t   padding1;
    uint16_t  eNB;
};

struct s1ap_100_EUTRAN_CGI {
    uint8_t  padding;
    uint8_t  PLMNId[3];
    uint32_t cellID;
};

#pragma pack(pop)

void
pie_0_MME_UE_ID(pdu_node_t *node, char *data, uint16_t size)
{
    // TODO: fix (13)
    pdu_node_mk("MME-UE-S1AP-ID", node, (char*)data, 0);
}

void
pie_1_HandoverType(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_2_Cause(pdu_node_t *node, char *data, uint16_t size)
{
    node = pdu_node_mk("Cause", node, data, size);
    pdu_node_mk("radioNetwork", node, data, 0);
}

void
pie_3_SourceID(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_4_TargetID(pdu_node_t *node, char *data, uint16_t size)
{
}

/* pid 5: unknown
 * pid 6: unknown
 * pid 7: unknown
 */

void
pie_8_ENB_UE_ID(pdu_node_t *node, char *data, uint16_t size)
{
    // TODO: fix (13)
    pdu_node_mk("ENB-UE-S1AP-ID", node, (char*)data, 0);
}

/* pid  9: unknown
 * pid 10: unknown
 * pid 11: unknown
 */

void
pie_12_ERABSubjecttoDataForwardingList(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_13_ERABtoReleaseListHOCmd(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_14_ERABDataForwardingItem(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_15_ERABReleaseItemBearerRelComp(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_16_ERABToBeSetupListBearerSUReq(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_17_ERABToBeSetupItemBearerSUReq(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_18_ERABAdmittedList(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_19_ERABFailedToSetupListHOReqAck(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_20_RABAdmittedItem(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_21_ERABFailedtoSetupItemHOReqAck(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_22_ERABToBeSwitchedDLList(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_23_ERABToBeSwitchedDLItem(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_24_ERABToBeSetupListCtxtSUReq(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_25_TraceActivation(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_26_NAS_PDU(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_27_ERABToBeSetupItemHOReq(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_28_ERABSetupListBearerSURes(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_29_ERABFailedToSetupListBearerSURes(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_30_ERABToBeModifiedListBearerModReq(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_31_ERABModifyListBearerModRes(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_32_ERABFailedToModifyList(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_33_ERABToBeReleasedList(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_34_ERABFailedToReleaseList(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_35_ERABItem(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_36_ERABToBeModifiedItemBearerModReq(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_37_ERABModifyItemBearerModRes(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_38_ERABReleaseItem(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_39_ERABSetupItemBearerSURes(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_40_SecurityContext(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_41_HandoverRestrictionList(pdu_node_t *node, char *data, uint16_t size)
{
}

/*
 * pid 42: unknown
 */

void
pie_43_UEPagingID(pdu_node_t *node, char *data, uint16_t size)
{
    node = pdu_node_mk("UEPagingID", node, data, size);
    node = pdu_node_mk("s-TMSI",     node, data, size);

    struct s1ap_43_UEPagingID *field = (void *)data;
    pdu_node_mk("mMEC",   node, (char*)&field->mmec, 0);
    pdu_node_mk("m-TMSI", node, (char*)&field->mtmsi, 0);
}

void
pie_44_pagingDRX(pdu_node_t *node, char *data, uint16_t size)
{
}

/*
 * pid 45: unknown
 */

void
pie_46_TAIList(pdu_node_t *node, char *data, uint16_t size)
{
    uint8_t *items = (void *)data;
    node = pdu_node_mk("TAIList", node, data, size);
    data++; size--;

    for (uint8_t item = 0; item <= *items; item++) {

        osi_s1ap_valitem_head_t *valitem = (void *)data;
        uint16_t valsize                 = bswap_16(valitem->critval) & 0xFFF;

        pdu_node_t *ie_item = pdu_node_mk("protocolIE-SingleContainer",
                node, data, size - sizeof(*valitem) - valsize);
        pdu_node_mk("id", ie_item, (char*)&valitem->id, 0);
        pdu_node_mkbitset("critically", ie_item, (char *)&valitem->critval, 6, 8);
        pdu_node_mkbitset("valueSize",  ie_item, (char *)&valitem->critval, 8, 16);

        data += sizeof(*valitem);
        s1ap_pie_func decode_func = s1ap_pies[bswap_16(valitem->id)].func;

        ie_item = pdu_node_mk("value", ie_item, (char*)data, valsize);

        if (decode_func) {
            decode_func(ie_item, (char*)data, valsize);
        }

        data += valsize;
    }
}

void
pie_47_TAIItem(pdu_node_t *node, char *data, uint16_t size)
{
    node = pdu_node_mk("TAIItem", node, data, size);

    struct s1ap_47_TAIItem *titem = (void *)data;
    pdu_node_mk("pLMNIdentity", node, (char *)&titem->PLMNId, 0);
    pdu_node_mk("tAC",          node, (char *)&titem->tAC, 0);
    // TODO: MCC, MNC here
}

void
pie_48_ERABFailedToSetupListCtxtSURes(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_49_ERABReleaseItemHOCmd(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_50_ERABSetupItemCtxtSURes(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_51_ERABSetupListCtxtSURes(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_52_ERABToBeSetupItemCtxtSUReq(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_53_ERABToBeSetupListHOReq(pdu_node_t *node, char *data, uint16_t size)
{
}

/*
 * pid 54: Unknown
 */

void
pie_55_GERANtoLTEHOInformationRes(pdu_node_t *node, char *data, uint16_t size)
{
}

/*
 * pid 56: Unknown
 */

void
pie_57_UTRANtoLTEHOInformationRes(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_58_CriticalityDiagnostics(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_59_Global_ENB_ID(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_60_eNBname(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_61_MMEname(pdu_node_t *node, char *data, uint16_t size)
{
}

/*
 * pid 62: Unknown
 */

void
pie_63_ServedPLMNs(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_64_SupportedTAs(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_65_TimeToWait(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_66_UEAggregateMaximumBitrate(pdu_node_t *node, char *data, uint16_t size)
{
    node = pdu_node_mk("UEAggregateMaximumBitrate", node, data, size);

    struct s1ap_66_UEAggregateMaximumBitrate *bt = (void *)data;
    pdu_node_mk("uEaggregateMaximumBitRateDL", node, (char *)&bt->uEaggregateMaximumBitRateDL, 0);
    pdu_node_mk("uEaggregateMaximumBitRateDL", node, (char *)&bt->uEaggregateMaximumBitRateUL, 0);
}

void
pie_67_TAI(pdu_node_t *node, char *data, uint16_t size)
{
    node = pdu_node_mk("TAI", node, data, size);

    struct s1ap_67_TAI *tai = (void *)data;
    pdu_node_mk("pLMNIdentity", node, (char *)&tai->PLMNId, 0);
    pdu_node_mk("tAC",          node, (char *)&tai->tAC, 0);
    // TODO: MCC, MNC here
}

/*
 * pid 68: Unknown
 */

void
pie_69_ERABReleaseListBearerRelComp(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_70_cdma2000PDU(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_71_cdma2000RATType(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_72_cdma2000SectorID(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_73_SecurityKey(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_74_UERadioCapability(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_75_GUMMEI_ID(pdu_node_t *node, char *data, uint16_t size)
{
}

/*
 * pid 76: unknown
 * pid 77: unknown
 */

void
pie_78_ERABInformationListItem(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_79_DirectForwardingPathAvailability(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_80_UEIdentityIndexValue(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_mk("UEIdentityIndexValue", node, (char*)data, 0);
}

/*
 * pid 81: unknown
 * pid 82: unknown
 */

void
pie_83_cdma2000HOStatus(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_84_cdma2000HORequiredIndication(pdu_node_t *node, char *data, uint16_t size)
{
}

/*
 * pid 85: unknown
 */

void
pie_86_EUTRANTraceID(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_87_RelativeMMECapacity(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_88_SourceMME_UE_S1AP_ID(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_89_BearersSubjectToStatusTransferItem(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_90_eNB_StatusTransferTransparentContainer(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_91_UE_associatedLogicalS1ConnectionItem(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_92_ResetType(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_93_UE_associatedLogicalS1ConnectionListResAck(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_94_ERABToBeSwitchedULItem(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_95_ERABToBeSwitchedULList(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_96_STMSI(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_97_cdma2000OneXRAND(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_98_RequestType(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_99_UE_S1AP_IDs(pdu_node_t *node, char *data, uint16_t size)
{
    node = pdu_node_mk("UE_S1AP_IDs", node, data, size);
    node = pdu_node_mk("uE-S1AP-ID-pair", node, data, size);

    struct s1ap_99_UE_S1AP_IDs *ids = (void *)data;
    pdu_node_mk("MME-UE-S1AP-ID", node, (char *)&ids->mMe, 0);
    pdu_node_mk("ENB-UE-S1AP-ID", node, (char *)&ids->eNB, 0);
}

void
pie_100_EUTRAN_CGI(pdu_node_t *node, char *data, uint16_t size)
{
    node = pdu_node_mk("EUTRAN-CGI", node, data, size);

    struct s1ap_100_EUTRAN_CGI *eutran = (void *)data;
    pdu_node_mk("pLMNIdentity", node, (char *)&eutran->PLMNId, 0);
    pdu_node_mk("cell-ID", node, (char *)&eutran->cellID, 0);
}

void
pie_101_OverloadResponse(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_102_cdma2000OneXSRVCCInfo(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_103_ERABFailedToBeReleasedList(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_104_SourceToTargetTransparentContainer(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_105_ServedGUMMEIs(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_106_SubscriberProfileIDforRFP(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_107_UESecurityCapabilities(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_108_CSFallbackIndicator(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_109_CNDomain(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_mk("CNDomain", node, (char*)data, 0);
}

void
pie_110_ERABReleasedList(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_111_MessageIdentifier(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_112_SerialNumber(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_113_WarningAreaList(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_114_RepetitionPeriod(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_115_NumberofBroadcastRequest(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_116_WarningType(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_117_WarningSecurityInfo(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_118_DataCodingScheme(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_119_WarningMessageContents(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_120_BroadcastCompletedAreaList(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_121_InterSystemInformationTransferTypeEDT(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_122_InterSystemInformationTransferTypeMDT(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_123_TargetToSourceTransparentContainer(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_124_SRVCCOperationPossible(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_125_SRVCCHOIndication(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_126_NASDownlinkCount(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_127_CSGId(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_128_CSGIdList(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_129_SONConfigurationTransferECT(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_130_SONConfigurationTransferMCT(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_131_TraceCollectionEntityIPAddress(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_132_MSClassmark2(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_133_MSClassmark3(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_134_RRCEstablishmentCause(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_mkbitset("RRC-Establishment-Cause", node, (char*)data, 4, 8);

}

void
pie_135_NASSecurityParametersFromEUTRAN(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_136_NASSecurityParametersToEUTRAN(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_137_DefaultPagingDRX(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_138_SourceToTargetTransparentContainerSecondary(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_139_TargetToSourceTransparentContainerSecondary(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_140_EUTRANRoundTripDelayEstimationInfo(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_141_BroadcastCancelledAreaList(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_142_ConcurrentWarningMessageIndicator(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_143_DataForwardingNotPossible(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_144_ExtendedRepetitionPeriod(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_145_CellAccessMode(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_146_CSGMembershipStatus(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_147_LPPaPDU(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_148_RoutingID(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_149_TimeSynchronizationInfo(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_150_PSServiceNotAvailable(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_151_PagingPriority(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_152_x2TNLConfigurationInfo(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_153_eNBX2ExtendedTransportLayerAddresses(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_154_GUMMEIList(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_155_GWTransportLayerAddress(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_156_CorrelationID(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_157_SourceMME_GUMMEI(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_158_MME_UE_S1AP_ID_2(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_159_RegisteredLAI(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_160_RelayNode_Indicator(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_161_TrafficLoadReductionIndication(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_162_MDTConfiguration(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_163_MMERelaySupportIndicator(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_164_GWContextReleaseIndication(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_165_ManagementBasedMDTAllowed(pdu_node_t *node, char *data, uint16_t size)
{
}

