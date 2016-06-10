#include <byteswap.h>

#include "s1ap.h"
#include "s1ap_fields.h"

static void
pid_0_MME_UE_ID(pdu_node_t *node, char *data, uint16_t size)
{
    // TODO: fix (13)
    pdu_node_mk("MME-UE-S1AP-ID", node, (char*)data, 0);
}

static void
pid_1_HandoverType(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_2_Cause(pdu_node_t *node, char *data, uint16_t size)
{
    node = pdu_node_mk("Cause", node, data, size);
    pdu_node_mk("radioNetwork", node, data, 0);
}

static void
pid_3_SourceID(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_4_TargetID(pdu_node_t *node, char *data, uint16_t size)
{
}

/* pid 5: unknown
 * pid 6: unknown
 * pid 7: unknown
 */

static void
pid_8_ENB_UE_ID(pdu_node_t *node, char *data, uint16_t size)
{
    // TODO: fix (13)
    pdu_node_mk("ENB-UE-S1AP-ID", node, (char*)data, 0);
}

/* pid  9: unknown
 * pid 10: unknown
 * pid 11: unknown
 */

static void
pid_12_ERABSubjecttoDataForwardingList(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_13_ERABtoReleaseListHOCmd(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_14_ERABDataForwardingItem(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_15_ERABReleaseItemBearerRelComp(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_16_ERABToBeSetupListBearerSUReq(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_17_ERABToBeSetupItemBearerSUReq(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_18_ERABAdmittedList(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_19_ERABFailedToSetupListHOReqAck(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_20_RABAdmittedItem(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_21_ERABFailedtoSetupItemHOReqAck(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_22_ERABToBeSwitchedDLList(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_23_ERABToBeSwitchedDLItem(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_24_ERABToBeSetupListCtxtSUReq(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_25_TraceActivation(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_26_NAS_PDU(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_27_ERABToBeSetupItemHOReq(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_28_ERABSetupListBearerSURes(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_29_ERABFailedToSetupListBearerSURes(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_30_ERABToBeModifiedListBearerModReq(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_31_ERABModifyListBearerModRes(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_32_ERABFailedToModifyList(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_33_ERABToBeReleasedList(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_34_ERABFailedToReleaseList(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_35_ERABItem(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_36_ERABToBeModifiedItemBearerModReq(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_37_ERABModifyItemBearerModRes(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_38_ERABReleaseItem(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_39_ERABSetupItemBearerSURes(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_40_SecurityContext(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_41_HandoverRestrictionList(pdu_node_t *node, char *data, uint16_t size)
{
}

/*
 * pid 42: unknown
 */

static void
pid_43_UEPagingID(pdu_node_t *node, char *data, uint16_t size)
{
    node = pdu_node_mk("UEPagingID", node, data, size);
    node = pdu_node_mk("s-TMSI",     node, data, size);

    struct s1ap_43_UEPagingID *field = (void *)data;
    pdu_node_mk("mMEC",   node, (char*)&field->mmec, 0);
    pdu_node_mk("m-TMSI", node, (char*)&field->mtmsi, 0);
}

static void
pid_44_pagingDRX(pdu_node_t *node, char *data, uint16_t size)
{
}

/*
 * pid 45: unknown
 */

static void
pid_46_TAIList(pdu_node_t *node, char *data, uint16_t size)
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
        s1ap_decfield_func decode_func;

        ie_item = pdu_node_mk("value", ie_item, (char*)data, valsize);

        s1ap_fields_getfunc(&decode_func, 0, bswap_16(valitem->id));

        if (decode_func) {
            decode_func(ie_item, (char*)data, valsize);
        }

        data += valsize;
    }
}

static void
pid_47_TAIItem(pdu_node_t *node, char *data, uint16_t size)
{
    node = pdu_node_mk("TAIItem", node, data, size);

    struct s1ap_47_TAIItem *titem = (void *)data;
    pdu_node_mk("pLMNIdentity", node, (char *)&titem->PLMNId, 0);
    pdu_node_mk("tAC",          node, (char *)&titem->tAC, 0);
    // TODO: MCC, MNC here
}

static void
pid_48_ERABFailedToSetupListCtxtSURes(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_49_ERABReleaseItemHOCmd(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_50_ERABSetupItemCtxtSURes(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_51_ERABSetupListCtxtSURes(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_52_ERABToBeSetupItemCtxtSUReq(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_53_ERABToBeSetupListHOReq(pdu_node_t *node, char *data, uint16_t size)
{
}

/*
 * pid 54: Unknown
 */

static void
pid_55_GERANtoLTEHOInformationRes(pdu_node_t *node, char *data, uint16_t size)
{
}

/*
 * pid 56: Unknown
 */

static void
pid_57_UTRANtoLTEHOInformationRes(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_58_CriticalityDiagnostics(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_59_Global_ENB_ID(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_60_eNBname(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_61_MMEname(pdu_node_t *node, char *data, uint16_t size)
{
}

/*
 * pid 62: Unknown
 */

static void
pid_63_ServedPLMNs(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_64_SupportedTAs(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_65_TimeToWait(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_66_UEAggregateMaximumBitrate(pdu_node_t *node, char *data, uint16_t size)
{
    node = pdu_node_mk("UEAggregateMaximumBitrate", node, data, size);

    struct s1ap_66_UEAggregateMaximumBitrate *bt = (void *)data;
    pdu_node_mk("uEaggregateMaximumBitRateDL", node, (char *)&bt->uEaggregateMaximumBitRateDL, 0);
    pdu_node_mk("uEaggregateMaximumBitRateDL", node, (char *)&bt->uEaggregateMaximumBitRateUL, 0);
}

static void
pid_67_TAI(pdu_node_t *node, char *data, uint16_t size)
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

static void
pid_69_ERABReleaseListBearerRelComp(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_70_cdma2000PDU(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_71_cdma2000RATType(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_72_cdma2000SectorID(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_73_SecurityKey(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_74_UERadioCapability(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_75_GUMMEI_ID(pdu_node_t *node, char *data, uint16_t size)
{
}

/*
 * pid 76: unknown
 * pid 77: unknown
 */

static void
pid_78_ERABInformationListItem(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_79_DirectForwardingPathAvailability(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_80_UEIdentityIndexValue(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_mk("UEIdentityIndexValue", node, (char*)data, 0);
}

/*
 * pid 81: unknown
 * pid 82: unknown
 */

static void
pid_83_cdma2000HOStatus(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_84_cdma2000HORequiredIndication(pdu_node_t *node, char *data, uint16_t size)
{
}

/*
 * pid 85: unknown
 */

static void
pid_86_EUTRANTraceID(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_87_RelativeMMECapacity(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_88_SourceMME_UE_S1AP_ID(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_89_BearersSubjectToStatusTransferItem(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_90_eNB_StatusTransferTransparentContainer(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_91_UE_associatedLogicalS1ConnectionItem(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_92_ResetType(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_93_UE_associatedLogicalS1ConnectionListResAck(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_94_ERABToBeSwitchedULItem(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_95_ERABToBeSwitchedULList(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_96_STMSI(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_97_cdma2000OneXRAND(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_98_RequestType(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_99_UE_S1AP_IDs(pdu_node_t *node, char *data, uint16_t size)
{
    node = pdu_node_mk("UE_S1AP_IDs", node, data, size);
    node = pdu_node_mk("uE-S1AP-ID-pair", node, data, size);

    struct s1ap_99_UE_S1AP_IDs *ids = (void *)data;
    pdu_node_mk("MME-UE-S1AP-ID", node, (char *)&ids->mMe, 0);
    pdu_node_mk("ENB-UE-S1AP-ID", node, (char *)&ids->eNB, 0);
}

static void
pid_100_EUTRAN_CGI(pdu_node_t *node, char *data, uint16_t size)
{
    node = pdu_node_mk("EUTRAN-CGI", node, data, size);

    struct s1ap_100_EUTRAN_CGI *eutran = (void *)data;
    pdu_node_mk("pLMNIdentity", node, (char *)&eutran->PLMNId, 0);
    pdu_node_mk("cell-ID", node, (char *)&eutran->cellID, 0);
}

static void
pid_101_OverloadResponse(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_102_cdma2000OneXSRVCCInfo(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_103_ERABFailedToBeReleasedList(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_104_SourceToTargetTransparentContainer(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_105_ServedGUMMEIs(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_106_SubscriberProfileIDforRFP(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_107_UESecurityCapabilities(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_108_CSFallbackIndicator(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_109_CNDomain(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_mk("CNDomain", node, (char*)data, 0);
}

static void
pid_110_ERABReleasedList(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_111_MessageIdentifier(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_112_SerialNumber(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_113_WarningAreaList(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_114_RepetitionPeriod(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_115_NumberofBroadcastRequest(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_116_WarningType(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_117_WarningSecurityInfo(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_118_DataCodingScheme(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_119_WarningMessageContents(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_120_BroadcastCompletedAreaList(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_121_InterSystemInformationTransferTypeEDT(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_122_InterSystemInformationTransferTypeMDT(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_123_TargetToSourceTransparentContainer(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_124_SRVCCOperationPossible(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_125_SRVCCHOIndication(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_126_NASDownlinkCount(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_127_CSGId(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_128_CSGIdList(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_129_SONConfigurationTransferECT(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_130_SONConfigurationTransferMCT(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_131_TraceCollectionEntityIPAddress(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_132_MSClassmark2(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_133_MSClassmark3(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_134_RRCEstablishmentCause(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_mkbitset("RRC-Establishment-Cause", node, (char*)data, 4, 8);

}

static void
pid_135_NASSecurityParametersFromEUTRAN(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_136_NASSecurityParametersToEUTRAN(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_137_DefaultPagingDRX(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_138_SourceToTargetTransparentContainerSecondary(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_139_TargetToSourceTransparentContainerSecondary(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_140_EUTRANRoundTripDelayEstimationInfo(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_141_BroadcastCancelledAreaList(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_142_ConcurrentWarningMessageIndicator(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_143_DataForwardingNotPossible(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_144_ExtendedRepetitionPeriod(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_145_CellAccessMode(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_146_CSGMembershipStatus(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_147_LPPaPDU(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_148_RoutingID(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_149_TimeSynchronizationInfo(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_150_PSServiceNotAvailable(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_151_PagingPriority(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_152_x2TNLConfigurationInfo(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_153_eNBX2ExtendedTransportLayerAddresses(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_154_GUMMEIList(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_155_GWTransportLayerAddress(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_156_CorrelationID(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_157_SourceMME_GUMMEI(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_158_MME_UE_S1AP_ID_2(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_159_RegisteredLAI(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_160_RelayNode_Indicator(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_161_TrafficLoadReductionIndication(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_162_MDTConfiguration(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_163_MMERelaySupportIndicator(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_164_GWContextReleaseIndication(pdu_node_t *node, char *data, uint16_t size)
{
}

static void
pid_165_ManagementBasedMDTAllowed(pdu_node_t *node, char *data, uint16_t size)
{
}


int s1ap_fields_getfunc(s1ap_decfield_func *decode_func,
                        uint8_t             procedure_code,
                        uint16_t            protocol_id)
{
    switch(protocol_id) {
    case 0: *decode_func = pid_0_MME_UE_ID;
        break;
    case 1: *decode_func = pid_1_HandoverType;
        break;
    case 2: *decode_func = pid_2_Cause;
        break;
    case 3: *decode_func = pid_3_SourceID;
        break;
    case 4: *decode_func = pid_4_TargetID;
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8: *decode_func = pid_8_ENB_UE_ID;
        break;
    case 9:
        break;
    case 10:
        break;
    case 11:
        break;
    case 12: *decode_func = pid_12_ERABSubjecttoDataForwardingList;
        break;
    case 13: *decode_func = pid_13_ERABtoReleaseListHOCmd;
        break;
    case 14: *decode_func = pid_14_ERABDataForwardingItem;
        break;
    case 15: *decode_func = pid_15_ERABReleaseItemBearerRelComp;
        break;
    case 16: *decode_func = pid_16_ERABToBeSetupListBearerSUReq;
        break;
    case 17: *decode_func = pid_17_ERABToBeSetupItemBearerSUReq;
        break;
    case 18: *decode_func = pid_18_ERABAdmittedList;
        break;
    case 19: *decode_func = pid_19_ERABFailedToSetupListHOReqAck;
        break;
    case 20: *decode_func = pid_20_RABAdmittedItem;
        break;
    case 21: *decode_func = pid_21_ERABFailedtoSetupItemHOReqAck;
        break;
    case 22: *decode_func = pid_22_ERABToBeSwitchedDLList;
        break;
    case 23: *decode_func = pid_23_ERABToBeSwitchedDLItem;
        break;
    case 24: *decode_func = pid_24_ERABToBeSetupListCtxtSUReq;
        break;
    case 25: *decode_func = pid_25_TraceActivation;
        break;
    case 26: *decode_func = pid_26_NAS_PDU;
        break;
    case 27: *decode_func = pid_27_ERABToBeSetupItemHOReq;
        break;
    case 28: *decode_func = pid_28_ERABSetupListBearerSURes;
        break;
    case 29: *decode_func = pid_29_ERABFailedToSetupListBearerSURes;
        break;
    case 30: *decode_func = pid_30_ERABToBeModifiedListBearerModReq;
        break;
    case 31: *decode_func = pid_31_ERABModifyListBearerModRes;
        break;
    case 32: *decode_func = pid_32_ERABFailedToModifyList;
        break;
    case 33: *decode_func = pid_33_ERABToBeReleasedList;
        break;
    case 34: *decode_func = pid_34_ERABFailedToReleaseList;
        break;
    case 35: *decode_func = pid_35_ERABItem;
        break;
    case 36: *decode_func = pid_36_ERABToBeModifiedItemBearerModReq;
        break;
    case 37: *decode_func = pid_37_ERABModifyItemBearerModRes;
        break;
    case 38: *decode_func = pid_38_ERABReleaseItem;
        break;
    case 39: *decode_func = pid_39_ERABSetupItemBearerSURes;
        break;



    case 40: *decode_func = pid_40_SecurityContext;
        break;
    case 41: *decode_func = pid_41_HandoverRestrictionList;
        break;
    case 42:
        break;
    case 43: *decode_func = pid_43_UEPagingID;
        break;
    case 44: *decode_func = pid_44_pagingDRX;
        break;
    case 45:
        break;
    case 46: *decode_func = pid_46_TAIList;
        break;
    case 47: *decode_func = pid_47_TAIItem;
        break;
    case 48: *decode_func = pid_48_ERABFailedToSetupListCtxtSURes;
        break;
    case 49: *decode_func = pid_49_ERABReleaseItemHOCmd;
        break;
    case 50: *decode_func = pid_50_ERABSetupItemCtxtSURes;
        break;
    case 51: *decode_func = pid_51_ERABSetupListCtxtSURes;
        break;
    case 52: *decode_func = pid_52_ERABToBeSetupItemCtxtSUReq;
        break;
    case 53: *decode_func = pid_53_ERABToBeSetupListHOReq;
        break;
    case 54:
        break;
    case 55: *decode_func = pid_55_GERANtoLTEHOInformationRes;
        break;
    case 56:
        break;
    case 57: *decode_func = pid_57_UTRANtoLTEHOInformationRes;
        break;
    case 58: *decode_func = pid_58_CriticalityDiagnostics;
        break;
    case 59: *decode_func = pid_59_Global_ENB_ID;
        break;
    case 60: *decode_func = pid_60_eNBname;
        break;
    case 61: *decode_func = pid_61_MMEname;
        break;
    case 62:
        break;
    case 63: *decode_func = pid_63_ServedPLMNs;
        break;
    case 64: *decode_func = pid_64_SupportedTAs;
        break;
    case 65: *decode_func = pid_65_TimeToWait;
        break;
    case 66: *decode_func = pid_66_UEAggregateMaximumBitrate;
        break;
    case 67: *decode_func = pid_67_TAI;
        break;
    case 68:
        break;
    case 69: *decode_func = pid_69_ERABReleaseListBearerRelComp;
        break;
    case 70: *decode_func = pid_70_cdma2000PDU;
        break;
    case 71: *decode_func = pid_71_cdma2000RATType;
        break;
    case 72: *decode_func = pid_72_cdma2000SectorID;
        break;
    case 73: *decode_func = pid_73_SecurityKey;
        break;
    case 74: *decode_func = pid_74_UERadioCapability;
        break;
    case 75: *decode_func = pid_75_GUMMEI_ID;
        break;
    case 76:
        break;
    case 77:
        break;
    case 78: *decode_func = pid_78_ERABInformationListItem;
        break;
    case 79: *decode_func = pid_79_DirectForwardingPathAvailability;
        break;



    case 80: *decode_func = pid_80_UEIdentityIndexValue;
        break;
    case 83: *decode_func = pid_83_cdma2000HOStatus;
        break;
    case 84: *decode_func = pid_84_cdma2000HORequiredIndication;
        break;

    case 86: *decode_func = pid_86_EUTRANTraceID;
        break;
    case 87: *decode_func = pid_87_RelativeMMECapacity;
        break;
    case 88: *decode_func = pid_88_SourceMME_UE_S1AP_ID;
        break;
    case 89: *decode_func = pid_89_BearersSubjectToStatusTransferItem;
        break;
    case 90: *decode_func = pid_90_eNB_StatusTransferTransparentContainer;
        break;
    case 91: *decode_func = pid_91_UE_associatedLogicalS1ConnectionItem;
        break;
    case 92: *decode_func = pid_92_ResetType;
        break;
    case 93: *decode_func = pid_93_UE_associatedLogicalS1ConnectionListResAck;
        break;
    case 94: *decode_func = pid_94_ERABToBeSwitchedULItem;
        break;
    case 95: *decode_func = pid_95_ERABToBeSwitchedULList;
        break;
    case 96: *decode_func = pid_96_STMSI;
        break;
    case 97: *decode_func = pid_97_cdma2000OneXRAND;
        break;
    case 98: *decode_func = pid_98_RequestType;
        break;
    case 99: *decode_func = pid_99_UE_S1AP_IDs;
        break;
    case 100: *decode_func = pid_100_EUTRAN_CGI;
        break;
    case 101: *decode_func = pid_101_OverloadResponse;
        break;
    case 102: *decode_func = pid_102_cdma2000OneXSRVCCInfo;
        break;
    case 103: *decode_func = pid_103_ERABFailedToBeReleasedList;
        break;
    case 104: *decode_func = pid_104_SourceToTargetTransparentContainer;
        break;
    case 105: *decode_func = pid_105_ServedGUMMEIs;
        break;
    case 106: *decode_func = pid_106_SubscriberProfileIDforRFP;
        break;
    case 107: *decode_func = pid_107_UESecurityCapabilities;
        break;
    case 108: *decode_func = pid_108_CSFallbackIndicator;
        break;
    case 109: *decode_func = pid_109_CNDomain;
        break;
    case 110: *decode_func = pid_110_ERABReleasedList;
        break;
    case 111: *decode_func = pid_111_MessageIdentifier;
        break;
    case 112: *decode_func = pid_112_SerialNumber;
        break;
    case 113: *decode_func = pid_113_WarningAreaList;
        break;
    case 114: *decode_func = pid_114_RepetitionPeriod;
        break;
    case 115: *decode_func = pid_115_NumberofBroadcastRequest;
        break;
    case 116: *decode_func = pid_116_WarningType;
        break;
    case 117: *decode_func = pid_117_WarningSecurityInfo;
        break;
    case 118: *decode_func = pid_118_DataCodingScheme;
        break;
    case 119: *decode_func = pid_119_WarningMessageContents;
        break;



    case 120: *decode_func = pid_120_BroadcastCompletedAreaList;
        break;
    case 121: *decode_func = pid_121_InterSystemInformationTransferTypeEDT;
        break;
    case 122: *decode_func = pid_122_InterSystemInformationTransferTypeMDT;
        break;
    case 123: *decode_func = pid_123_TargetToSourceTransparentContainer;
        break;
    case 124: *decode_func = pid_124_SRVCCOperationPossible;
        break;
    case 125: *decode_func = pid_125_SRVCCHOIndication;
        break;
    case 126: *decode_func = pid_126_NASDownlinkCount;
        break;
    case 127: *decode_func = pid_127_CSGId;
        break;
    case 128: *decode_func = pid_128_CSGIdList;
        break;
    case 129: *decode_func = pid_129_SONConfigurationTransferECT;
        break;
    case 130: *decode_func = pid_130_SONConfigurationTransferMCT;
        break;
    case 131: *decode_func = pid_131_TraceCollectionEntityIPAddress;
        break;
    case 132: *decode_func = pid_132_MSClassmark2;
        break;
    case 133: *decode_func = pid_133_MSClassmark3;
        break;
    case 134: *decode_func = pid_134_RRCEstablishmentCause;
        break;
    case 135: *decode_func = pid_135_NASSecurityParametersFromEUTRAN;
        break;
    case 136: *decode_func = pid_136_NASSecurityParametersToEUTRAN;
        break;
    case 137: *decode_func = pid_137_DefaultPagingDRX;
        break;
    case 138: *decode_func = pid_138_SourceToTargetTransparentContainerSecondary;
        break;
    case 139: *decode_func = pid_139_TargetToSourceTransparentContainerSecondary;
        break;
    case 140: *decode_func = pid_140_EUTRANRoundTripDelayEstimationInfo;
        break;
    case 141: *decode_func = pid_141_BroadcastCancelledAreaList;
        break;
    case 142: *decode_func = pid_142_ConcurrentWarningMessageIndicator;
        break;
    case 143: *decode_func = pid_143_DataForwardingNotPossible;
        break;
    case 144: *decode_func = pid_144_ExtendedRepetitionPeriod;
        break;
    case 145: *decode_func = pid_145_CellAccessMode;
        break;
    case 146: *decode_func = pid_146_CSGMembershipStatus;
        break;
    case 147: *decode_func = pid_147_LPPaPDU;
        break;
    case 148: *decode_func = pid_148_RoutingID;
        break;
    case 149: *decode_func = pid_149_TimeSynchronizationInfo;
        break;
    case 150: *decode_func = pid_150_PSServiceNotAvailable;
        break;
    case 151: *decode_func = pid_151_PagingPriority;
        break;
    case 152: *decode_func = pid_152_x2TNLConfigurationInfo;
        break;
    case 153: *decode_func = pid_153_eNBX2ExtendedTransportLayerAddresses;
        break;
    case 154: *decode_func = pid_154_GUMMEIList;
        break;
    case 155: *decode_func = pid_155_GWTransportLayerAddress;
        break;
    case 156: *decode_func = pid_156_CorrelationID;
        break;
    case 157: *decode_func = pid_157_SourceMME_GUMMEI;
        break;
    case 158: *decode_func = pid_158_MME_UE_S1AP_ID_2;
        break;
    case 159: *decode_func = pid_159_RegisteredLAI;
        break;



    case 160: *decode_func = pid_160_RelayNode_Indicator;
        break;
    case 161: *decode_func = pid_161_TrafficLoadReductionIndication;
        break;
    case 162: *decode_func = pid_162_MDTConfiguration;
        break;
    case 163: *decode_func = pid_163_MMERelaySupportIndicator;
        break;
    case 164: *decode_func = pid_164_GWContextReleaseIndication;
        break;
    case 165: *decode_func = pid_165_ManagementBasedMDTAllowed;
        break;


    default: *decode_func = NULL;
    }
    return 0;
}
