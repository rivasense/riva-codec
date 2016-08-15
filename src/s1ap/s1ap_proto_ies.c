#include <byteswap.h>

#include "s1ap.h"
#include "s1ap_dict.h"
#include "s1ap_proto_ies.h"


static void
__pLMNidentity(pdu_node_t *node)
{
    node = pdu_node_mknext("PLMNidentity", node);
    //pdu_node_mknext("MCC", node);
    //pdu_node_mknext("MNC", node);
}

static void
__ERABId(pdu_node_t *node, uint16_t offset, uint8_t bytes)
{
    pdu_node_t *erabid = pdu_node_mk("e-RAB-ID", node);
    pdu_node_cursor(node, bytes, PDU_CURSOFF_INC);

    erabid->val.size        = bytes;
    erabid->dict->mask_bitlen = 4;
    erabid->dict->mask_offset = (erabid->val.size << 3) - erabid->dict->mask_bitlen - offset;
    erabid->dict->mask = 0b1111 << erabid->dict->mask_offset;
}

void
pie_0_MME_UE_ID(pdu_node_t *node, char *data, uint16_t size)
{
    if (size > sizeof(uint32_t)) {
        pdu_node_cursor(node, size - sizeof(uint32_t), PDU_CURSOFF_INC);
    }
    pdu_node_mk("MME-UE-S1AP-ID", node);
}

void
pie_1_HandoverType(pdu_node_t *node, char *data, uint16_t size)
{
    if (size > sizeof(uint8_t)) {
        pdu_node_cursor(node, size - sizeof(uint8_t), PDU_CURSOFF_INC);
    }
    pdu_node_mk("HandoverType", node);
}

void
pie_2_Cause(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_t *ncause = pdu_node_mk("Cause", node);
    uint8_t     vcause;
    pdu_node_get_value(ncause, &vcause);

    switch (vcause) {
    case 0: pdu_node_mk("radioNetwork", ncause); break;
    case 1: pdu_node_mk("transport",    ncause); break;
    case 2: pdu_node_mk("nas",          ncause); break;
    case 3: pdu_node_mk("protocol",     ncause); break;
    case 4: pdu_node_mk("misc",         ncause); break;
    }
}

void
pie_3_SourceID(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_4_TargetID(pdu_node_t *node, char *data, uint16_t size)
{
    uint8_t targetid;

    node = pdu_node_mknext("TargetID", node);
    pdu_node_get_value(node, &targetid);

    if (targetid == 0) {
        pdu_node_t *tenb = pdu_node_mkdatasize("targeteNB-ID", node, data + 1, size - 1);

        /* global ENB ID */
        __pLMNidentity(tenb);

        uint8_t     genb_id_v;
        pdu_node_t *genb_id = pdu_node_mknext("eNB-ID", tenb);
        pdu_node_get_value(genb_id, &genb_id_v);
        if (genb_id_v == 0) {
            pdu_node_mknext("macroENB-ID", tenb);
        } else {
            pdu_node_mknext("homeENB-ID", tenb);
        }


        /* selected TAI */
        __pLMNidentity(tenb);
        pdu_node_mknext("tAC", tenb);
    }

    if (targetid == 1) {
        pdu_node_t *trnc = pdu_node_mkdatasize("targetRNC-ID", node, data + 2, size - 2);
        __pLMNidentity(trnc);
        pdu_node_mknext("lAC", trnc);
        pdu_node_mknext("rAC", trnc);
        pdu_node_mknext("rNC-ID", trnc);
    }
}

/* pid 5: unknown
 * pid 6: unknown
 * pid 7: unknown
 */

void
pie_8_ENB_UE_ID(pdu_node_t *node, char *data, uint16_t size)
{
    if (size > sizeof(uint16_t)) {
        pdu_node_cursor(node, size - sizeof(uint16_t), PDU_CURSOFF_INC);
    }
    pdu_node_mknext("ENB-UE-S1AP-ID", node);
}

/* pid  9: unknown
 * pid 10: unknown
 * pid 11: unknown
 */

/* CHECK: 12 -> 14 (2584 pack) */
void
pie_12_ERABSubjecttoDataForwardingList(pdu_node_t *node, char *data, uint16_t size)
{
    s1ap_decode_list(node,
                    "E-RABSubjecttoDataForwardingList",
                    "E-RABDataForwardingItem",
                    data, size);
}

void
pie_13_ERABtoReleaseListHOCmd(pdu_node_t *node, char *data, uint16_t size)
{
}

/* CHECK: 14 (2584 pack) */
void
pie_14_ERABDataForwardingItem(pdu_node_t *node, char *data, uint16_t size)
{
    __ERABId(node, 7, 2);
    /* ... dL-transportLayerAddress  */
    /* ... dL-gTP-TEID  */
}

/* CHECK: 15 (5712 pack) */
void
pie_15_ERABReleaseItemBearerRelComp(pdu_node_t *node, char *data, uint16_t size)
{
    __ERABId(node, 3, 1);
}

/* CHECK: 16 -> 17 (18464 pack) */
void
pie_16_ERABToBeSetupListBearerSUReq(pdu_node_t *node, char *data, uint16_t size)
{
    s1ap_decode_list(node,
                    "E-RABToBeSetupListBearerSUReq",
                    "E-RABToBeSetupItemBearerSUReq",
                    data, size);

}

/* CHECK: 17 (18464 pack) */
void
pie_17_ERABToBeSetupItemBearerSUReq(pdu_node_t *node, char *data, uint16_t size)
{
/*
    e_RAB_ID
    e_RABlevelQoSParameters
    transportLayerAddress
    gTP_TEID
    nAS_PDU
    iE_Extensions
*/
    /* e_RAB_ID */
    __ERABId(node, 3, 1);
    /* e_RABlevelQoSParameters */
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC);
    pdu_node_mknext("qCI", node);
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC); // skip allocationRetensionPriority fieldset
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC); // skip Extension Present bit fieldset
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC); // padding
    /* transportLayerAddress:: skip */
    pdu_node_cursor(node, 4, PDU_CURSOFF_INC);
    /* gTP-TEID */
    pdu_node_mknext("gTP-TEID", node);

}

/* CHECK: 18 -> 20 (2815 pack) */
void
pie_18_ERABAdmittedList(pdu_node_t *node, char *data, uint16_t size)
{
    s1ap_decode_list(node,
                    "E-RABAdmittedList",
                    "E-RABAdmittedItem",
                    data, size);
}

void
pie_19_ERABFailedToSetupListHOReqAck(pdu_node_t *node, char *data, uint16_t size)
{
}

/* CHECK: 20 (2815 pack) */
void
pie_20_RABAdmittedItem(pdu_node_t *node, char *data, uint16_t size)
{
    __ERABId(node, 7, 2);
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC); // padding
    pdu_node_cursor(node, 4, PDU_CURSOFF_INC); // transportLayerAddress
    pdu_node_mknext("gTP-TEID", node);
}

void
pie_21_ERABFailedtoSetupItemHOReqAck(pdu_node_t *node, char *data, uint16_t size)
{
}

/* CHECK: 22 -> 23 (2546 pack) */
void
pie_22_ERABToBeSwitchedDLList(pdu_node_t *node, char *data, uint16_t size)
{
    s1ap_decode_list(node,
                    "E-RABToBeSwitchedDLList",
                    "E-RABToBeSwitchedDLItem",
                    data, size);
}

/* CHECK: 23 (2546 pack) */
void
pie_23_ERABToBeSwitchedDLItem(pdu_node_t *node, char *data, uint16_t size)
{
    __ERABId(node, 3, 2);
    pdu_node_cursor(node, 4, PDU_CURSOFF_INC); // skip transportLayerAddress
    pdu_node_mknext("gTP-TEID", node);
}

/* CHECK: 24 -> 52 (21 pack) */
void
pie_24_ERABToBeSetupListCtxtSUReq(pdu_node_t *node, char *data, uint16_t size)
{
    s1ap_decode_list(node,
                    "E-RABToBeSetupListCtxtSUReq",
                    "E-RABToBeSetupItemCtxtSUReq",
                    data, size);
}

void
pie_25_TraceActivation(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_26_NAS_PDU(pdu_node_t *node, char *data, uint16_t size)
{
}

/* CHECK: 27 (2813 pack) */
void
pie_27_ERABToBeSetupItemHOReq(pdu_node_t *node, char *data, uint16_t size)
{
    __ERABId(node, 3, 2);
    pdu_node_cursor(node, 4, PDU_CURSOFF_INC); // skip transportLayerAddress
    pdu_node_mknext("gTP-TEID", node);
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC); // padding
    pdu_node_mknext("qCI", node);
}

/* CHECK: 28 -> 39 (18646 packet) */
void
pie_28_ERABSetupListBearerSURes(pdu_node_t *node, char *data, uint16_t size)
{
    s1ap_decode_list(node,
                    "E-RABSetupListBearerSURes",
                    "E-RABSetupItemBearerSURes",
                    data, size);
}

void
pie_29_ERABFailedToSetupListBearerSURes(pdu_node_t *node, char *data, uint16_t size)
{
    // container 29 -> 27
}

/* CHECK: 30 -> 36 (1927 pack) */
void
pie_30_ERABToBeModifiedListBearerModReq(pdu_node_t *node, char *data, uint16_t size)
{
    s1ap_decode_list(node,
                    "E-RABToBeModifiedListBearerModReq",
                    "E-RABToBeModifiedItemBearerModReq",
                    data, size);
}

/* CHECK: 31 -> 37 (5742 pack) */
void
pie_31_ERABModifyListBearerModRes(pdu_node_t *node, char *data, uint16_t size)
{
    s1ap_decode_list(node,
                    "E-RABModifyListBearerModRes",
                    "E-RABModifyItemBearerModRes",
                    data, size);
}

void
pie_32_ERABFailedToModifyList(pdu_node_t *node, char *data, uint16_t size)
{
}

/* CHECK: 33 -> 35 (5707 pack) */
void
pie_33_ERABToBeReleasedList(pdu_node_t *node, char *data, uint16_t size)
{
    s1ap_decode_list(node,
                    "E-RABList",
                    "E-RABItem",
                    data, size);
}

void
pie_34_ERABFailedToReleaseList(pdu_node_t *node, char *data, uint16_t size)
{
    // container 34 -> 35
}

/* CHECK: 35 (5707 pack) */
void
pie_35_ERABItem(pdu_node_t *node, char *data, uint16_t size)
{
    __ERABId(node, 3, 1);
    // TODO: cause
}

/* CHECK: 36 (1927 pack) */
void
pie_36_ERABToBeModifiedItemBearerModReq(pdu_node_t *node, char *data, uint16_t size)
{
    /* e_RAB_ID */
    __ERABId(node, 3, 1);
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC); // padding
    pdu_node_mknext("qCI", node);
}

/* CHECK: 37 (5742 pack) */
void
pie_37_ERABModifyItemBearerModRes(pdu_node_t *node, char *data, uint16_t size)
{
    __ERABId(node, 3, 1);
    //pdu_node_mknext("e-RAB-ID", node);
}

void
pie_38_ERABReleaseItem(pdu_node_t *node, char *data, uint16_t size)
{
}

/* CHECK: 39 (18646 packet) */
void
pie_39_ERABSetupItemBearerSURes(pdu_node_t *node, char *data, uint16_t size)
{
    __ERABId(node, 3, 2);
    pdu_node_cursor(node, 4, PDU_CURSOFF_INC); // skip transportLayerAddress
    pdu_node_mknext("gTP-TEID", node);
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

/* TODO: 43 (34 pack) */
void
pie_43_UEPagingID(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_mknext("mMEC", node); // TODO: mMMEC decode
    pdu_node_mknext("m-TMSI",  node);}

void
pie_44_pagingDRX(pdu_node_t *node, char *data, uint16_t size)
{
}

/*
 * pid 45: unknown
 */
/* TODO: 46 -> 47 (34 pack) */
void
pie_46_TAIList(pdu_node_t *node, char *data, uint16_t size)
{
    s1ap_decode_list(node,
                    "TAIList",
                    "TAIItem",
                    data, size);
}

void
pie_47_TAIItem(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC);
    __pLMNidentity(node);
    pdu_node_mknext("tAC", node);
}

void
pie_48_ERABFailedToSetupListCtxtSURes(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_49_ERABReleaseItemHOCmd(pdu_node_t *node, char *data, uint16_t size)
{
}

/* CHECK: 50 (5 pack) */
void
pie_50_ERABSetupItemCtxtSURes(pdu_node_t *node, char *data, uint16_t size)
{
    __ERABId(node, 3, 2);
    pdu_node_cursor(node, 4, PDU_CURSOFF_INC); // skip transportLayerAddress
    pdu_node_mknext("gTP-TEID", node);
}

/* CHECK: 51 -> 50 (5 pack) */
void
pie_51_ERABSetupListCtxtSURes(pdu_node_t *node, char *data, uint16_t size)
{
    s1ap_decode_list(node,
                    "E-RABSetupListCtxtSURes",
                    "E-RABSetupItemCtxtSURes",
                    data, size);
}

/* CHECK: 52 (21 pack) */
void
pie_52_ERABToBeSetupItemCtxtSUReq(pdu_node_t *node, char *data, uint16_t size)
{
    /* e_RAB_ID */
    __ERABId(node, 4, 1);
    /* e_RABlevelQoSParameters */
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC); // padding
    pdu_node_mknext("qCI", node);
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC); // skip allocationRetensionPriority fieldset
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC); // skip Extension Present bit fieldset
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC); // padding
    /* transportLayerAddress:: skip */
    pdu_node_cursor(node, 4, PDU_CURSOFF_INC);
    /* gTP-TEID */
    pdu_node_mknext("gTP-TEID", node);
}

/* CHECK: 53 -> 27 (2813 pack) */
void
pie_53_ERABToBeSetupListHOReq(pdu_node_t *node, char *data, uint16_t size)
{
    s1ap_decode_list(node,
                    "E-RABToBeSetupListHOReq",
                    "E-RABToBeSetupItemHOReq",
                    data, size);
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
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC);
    __pLMNidentity(node);

    uint8_t     genb_id_v;
    pdu_node_t *genb_id = pdu_node_mknext("eNB-ID", node);
    pdu_node_get_value(genb_id, &genb_id_v);
    if (genb_id_v == 0) {
        pdu_node_mknext("macroENB-ID", node);
    } else {
        pdu_node_mknext("homeENB-ID", node);
    }
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
    pdu_node_mk("tAC", node);
}

void
pie_65_TimeToWait(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_66_UEAggregateMaximumBitrate(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC);
    pdu_node_mknext("uEaggregateMaximumBitRateDL", node);

    pdu_node_cursor(node, 1, PDU_CURSOFF_INC);
    pdu_node_mknext("uEaggregateMaximumBitRateUL", node);
}

void
pie_67_TAI(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC);
    __pLMNidentity(node);
    pdu_node_mk("tAC", node);
}

/*
 * pid 68: Unknown
 */

/* CHECK: 69 -> 15 (5712 pack) */
void
pie_69_ERABReleaseListBearerRelComp(pdu_node_t *node, char *data, uint16_t size)
{
    s1ap_decode_list(node,
                    "E-RABReleaseListBearerRelComp",
                    "E-RABReleaseItemBearerRelComp",
                    data, size);
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
    pdu_node_mk("cell-ID",  node);
    pdu_node_mk("e-RAB-ID", node);
}

void
pie_79_DirectForwardingPathAvailability(pdu_node_t *node, char *data, uint16_t size)
{
}

void
pie_80_UEIdentityIndexValue(pdu_node_t *node, char *data, uint16_t size)
{
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

/* CHECK: 89 (2821 packet) */
void
pie_89_BearersSubjectToStatusTransferItem(pdu_node_t *node, char *data, uint16_t size)
{
    __ERABId(node, 4, 1);
}

/* CHECK: 90 -> 89 (2821 packet) */
void
pie_90_eNB_StatusTransferTransparentContainer(pdu_node_t *node, char *data, uint16_t size)
{
    s1ap_decode_list(node,
                    "eNB-StatusTransfer-TransparentContainer",
                    "Bearers-SubjectToStatusTransfer-Item",
                     data, size);
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

/* CHECK: 94 (2567 packet) */
void
pie_94_ERABToBeSwitchedULItem(pdu_node_t *node, char *data, uint16_t size)
{
    __ERABId(node, 3, 2);
    pdu_node_cursor(node, 4, PDU_CURSOFF_INC); // skip transportLayerAddress
    pdu_node_mknext("gTP-TEID", node);
}

/* CHECK: 95 -> 94 (2567 packet) */
void
pie_95_ERABToBeSwitchedULList(pdu_node_t *node, char *data, uint16_t size)
{
    s1ap_decode_list(node,
                    "E-RABToBeSwitchedULList",
                    "E-RABToBeSwitchedULItem",
                    data, size);
}

/* CHECK: 96 (16 packet) */
void
pie_96_STMSI(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_mknext("mMEC", node); // TODO: mMMEC decode
    pdu_node_mknext("m-TMSI",  node);
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
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC);
    pdu_node_mknext("MME-UE-S1AP-ID", node);

    pdu_node_cursor(node, 1, PDU_CURSOFF_INC);
    pdu_node_mknext("ENB-UE-S1AP-ID", node);
}

/* CHECK: 100 (8 packet) */
void
pie_100_EUTRAN_CGI(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC);
    __pLMNidentity(node);
    pdu_node_mknext("cell-ID", node);

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
    // container ?? RABInformationListInfo (??)
}

/* TODO: 105 (29724 packet) */
void
pie_105_ServedGUMMEIs(pdu_node_t *node, char *data, uint16_t size)
{
    pdu_node_cursor(node, 1, PDU_CURSOFF_INC);
    __pLMNidentity(node);

    pdu_node_mk("mME-Group-ID", node);
    pdu_node_mk("mME-Code", node);
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
    pdu_node_mk("CNDomain", node);
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
    pdu_node_mk("RRC-Establishment-Cause", node);
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

