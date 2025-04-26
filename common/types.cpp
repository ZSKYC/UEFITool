/* types.cpp
 
 Copyright (c) 2016, Nikolaj Schlej. All rights reserved.
 This program and the accompanying materials
 are licensed and made available under the terms and conditions of the BSD License
 which accompanies this distribution.  The full text of the license may be found at
 http://opensource.org/licenses/bsd-license.php
 
 THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 WITHWARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */

#include "ustring.h"
#include "types.h"
#include "ffs.h"
#include "intel_fit.h"

UString regionTypeToUString(const UINT8 type)
{
    switch (type) {
        case Subtypes::DescriptorRegion:  return UString("Descriptor");
        case Subtypes::BiosRegion:        return UString("BIOS");
        case Subtypes::MeRegion:          return UString("ME");
        case Subtypes::GbeRegion:         return UString("GbE");
        case Subtypes::PdrRegion:         return UString("PDR");
        case Subtypes::DevExp1Region:     return UString("DevExp1");
        case Subtypes::Bios2Region:       return UString("BIOS2");
        case Subtypes::MicrocodeRegion:   return UString("Microcode");
        case Subtypes::EcRegion:          return UString("EC");
        case Subtypes::DevExp2Region:     return UString("DevExp2");
        case Subtypes::IeRegion:          return UString("IE");
        case Subtypes::Tgbe1Region:       return UString("10GbE1");
        case Subtypes::Tgbe2Region:       return UString("10GbE2");
        case Subtypes::Reserved1Region:   return UString("Reserved1");
        case Subtypes::Reserved2Region:   return UString("Reserved2");
        case Subtypes::PttRegion:         return UString("PTT");
    };
    
    return  usprintf("Unknown 0x%02X", type);
}

UString itemTypeToUString(const UINT8 type)
{
    switch (type) {
        case Types::Root:                       return UString("Root");
        case Types::Image:                      return UString("Image");
        case Types::Capsule:                    return UString("Capsule");
        case Types::Region:                     return UString("Region");
        case Types::Volume:                     return UString("Volume");
        case Types::Padding:                    return UString("Padding");
        case Types::File:                       return UString("File");
        case Types::Section:                    return UString("Section");
        case Types::FreeSpace:                  return UString("Free space");
        case Types::VssStore:                   return UString("VSS store");
        case Types::Vss2Store:                  return UString("VSS2 store");
        case Types::FtwStore:                   return UString("FTW store");
        case Types::FdcStore:                   return UString("FDC store");
        case Types::SysFStore:                  return UString("SysF store");
        case Types::EvsaStore:                  return UString("EVSA store");
        case Types::CmdbStore:                  return UString("CMDB store");
        case Types::PhoenixFlashMapStore:       return UString("FlashMap store");
        case Types::InsydeFlashDeviceMapStore:  return UString("FlashDeviceMap store");
        case Types::DellDvarStore:              return UString("DVAR store");
        case Types::NvarGuidStore:              return UString("NVAR GUID store");
        case Types::NvarEntry:                  return UString("NVAR entry");
        case Types::VssEntry:                   return UString("VSS entry");
        case Types::SysFEntry:                  return UString("SysF entry");
        case Types::EvsaEntry:                  return UString("EVSA entry");
        case Types::PhoenixFlashMapEntry:       return UString("FlashMap entry");
        case Types::InsydeFlashDeviceMapEntry:  return UString("FlashDeviceMap entry");
        case Types::DellDvarEntry:              return UString("DVAR entry");
        case Types::Microcode:                  return UString("Microcode");
        case Types::SlicData:                   return UString("SLIC data");
        case Types::FptStore:                   return UString("FPT store");
        case Types::FptEntry:                   return UString("FPT entry");
        case Types::IfwiHeader:                 return UString("IFWI header");
        case Types::IfwiPartition:              return UString("IFWI partition");
        case Types::FptPartition:               return UString("FPT partition");
        case Types::BpdtStore:                  return UString("BPDT store");
        case Types::BpdtEntry:                  return UString("BPDT entry");
        case Types::BpdtPartition:              return UString("BPDT partition");
        case Types::CpdStore:                   return UString("CPD store");
        case Types::CpdEntry:                   return UString("CPD entry");
        case Types::CpdPartition:               return UString("CPD partition");
        case Types::CpdExtension:               return UString("CPD extension");
        case Types::CpdSpiEntry:                return UString("CPD SPI entry");
        case Types::StartupApDataEntry:         return UString("Startup AP data");
    }
    
    return usprintf("Unknown 0x%02X", type);
}

UString itemSubtypeToUString(const UINT8 type, const UINT8 subtype)
{
    switch (type) {
        case Types::Image:
            if      (subtype == Subtypes::IntelImage)                   return UString("Intel");
            else if (subtype == Subtypes::UefiImage)                    return UString("UEFI");
            break;
        case Types::Padding:
            if      (subtype == Subtypes::ZeroPadding)                  return UString("Empty (0x00)");
            else if (subtype == Subtypes::OnePadding)                   return UString("Empty (0xFF)");
            else if (subtype == Subtypes::DataPadding)                  return UString("Non-empty");
            break;
        case Types::Volume:
            if      (subtype == Subtypes::UnknownVolume)                return UString("Unknown");
            else if (subtype == Subtypes::Ffs2Volume)                   return UString("FFSv2");
            else if (subtype == Subtypes::Ffs3Volume)                   return UString("FFSv3");
            else if (subtype == Subtypes::NvramVolume)                  return UString("NVRAM");
            else if (subtype == Subtypes::MicrocodeVolume)              return UString("Microcode");
            break;
        case Types::Capsule:
            if      (subtype == Subtypes::AptioSignedCapsule)           return UString("Aptio signed");
            else if (subtype == Subtypes::AptioUnsignedCapsule)         return UString("Aptio unsigned");
            else if (subtype == Subtypes::UefiCapsule)                  return UString("UEFI 2.0");
            else if (subtype == Subtypes::ToshibaCapsule)               return UString("Toshiba");
            break;
        case Types::Region:                                             return regionTypeToUString(subtype);
        case Types::File:                                               return fileTypeToUString(subtype);
        case Types::Section:                                            return sectionTypeToUString(subtype);
        case Types::NvarEntry:
            if      (subtype == Subtypes::InvalidNvarEntry)             return UString("Invalid");
            else if (subtype == Subtypes::InvalidLinkNvarEntry)         return UString("Invalid link");
            else if (subtype == Subtypes::LinkNvarEntry)                return UString("Link");
            else if (subtype == Subtypes::DataNvarEntry)                return UString("Data");
            else if (subtype == Subtypes::FullNvarEntry)                return UString("Full");
            break;
        case Types::VssEntry:
            if      (subtype == Subtypes::InvalidVssEntry)              return UString("Invalid");
            else if (subtype == Subtypes::StandardVssEntry)             return UString("Standard");
            else if (subtype == Subtypes::AppleVssEntry)                return UString("Apple");
            else if (subtype == Subtypes::AuthVssEntry)                 return UString("Auth");
            else if (subtype == Subtypes::IntelVssEntry)                return UString("Intel");
            break;
        case Types::SysFEntry:
            if      (subtype == Subtypes::InvalidSysFEntry)             return UString("Invalid");
            else if (subtype == Subtypes::NormalSysFEntry)              return UString("Normal");
            break;
        case Types::EvsaEntry:
            if      (subtype == Subtypes::InvalidEvsaEntry)             return UString("Invalid");
            else if (subtype == Subtypes::UnknownEvsaEntry)             return UString("Unknown");
            else if (subtype == Subtypes::GuidEvsaEntry)                return UString("GUID");
            else if (subtype == Subtypes::NameEvsaEntry)                return UString("Name");
            else if (subtype == Subtypes::DataEvsaEntry)                return UString("Data");
            break;
        case Types::PhoenixFlashMapEntry:
            if      (subtype == Subtypes::VolumeFlashMapEntry)          return UString("Volume");
            else if (subtype == Subtypes::DataFlashMapEntry)            return UString("Data");
            else if (subtype == Subtypes::UnknownFlashMapEntry)         return UString("Unknown");
            break;
        case Types::DellDvarEntry:
            if      (subtype == Subtypes::InvalidDvarEntry)             return UString("Invalid");
            else if (subtype == Subtypes::NamespaceGuidDvarEntry)       return UString("NamespaceGuid");
            else if (subtype == Subtypes::NameIdDvarEntry)              return UString("NameId");
            else if (subtype == Subtypes::UnknownDvarEntry)             return UString("Unknown");
            break;
        case Types::Microcode:
            if      (subtype == Subtypes::IntelMicrocode)               return UString("Intel");
            else if (subtype == Subtypes::AmdMicrocode)                 return UString("AMD");
            break;
        case Types::FptEntry:
            if      (subtype == Subtypes::ValidFptEntry)                return UString("Valid");
            else if (subtype == Subtypes::InvalidFptEntry)              return UString("Invalid");
            break;
        case Types::FptPartition:
            if      (subtype == Subtypes::CodeFptPartition)             return UString("Code");
            else if (subtype == Subtypes::DataFptPartition)             return UString("Data");
            else if (subtype == Subtypes::GlutFptPartition)             return UString("GLUT");
            break;
        case Types::IfwiPartition:
            if      (subtype == Subtypes::BootIfwiPartition)            return UString("Boot");
            else if (subtype == Subtypes::DataIfwiPartition)            return UString("Data");
            break;
        case Types::CpdPartition:
            if      (subtype == Subtypes::ManifestCpdPartition)         return UString("Manifest");
            else if (subtype == Subtypes::MetadataCpdPartition)         return UString("Metadata");
            else if (subtype == Subtypes::KeyCpdPartition)              return UString("Key");
            else if (subtype == Subtypes::CodeCpdPartition)             return UString("Code");
            break;
        case Types::StartupApDataEntry:
            if      (subtype == Subtypes::x86128kStartupApDataEntry)    return UString("X86 128K");
            break;
    }
    
    return UString();
}

UString compressionTypeToUString(const UINT8 algorithm)
{
    switch (algorithm) {
        case COMPRESSION_ALGORITHM_NONE:                    return UString("None");
        case COMPRESSION_ALGORITHM_EFI11:                   return UString("EFI 1.1");
        case COMPRESSION_ALGORITHM_TIANO:                   return UString("Tiano");
        case COMPRESSION_ALGORITHM_UNDECIDED:               return UString("Undecided Tiano/EFI 1.1");
        case COMPRESSION_ALGORITHM_LZMA:                    return UString("LZMA");
        case COMPRESSION_ALGORITHM_LZMA_INTEL_LEGACY:       return UString("Intel legacy LZMA");
        case COMPRESSION_ALGORITHM_LZMAF86:                 return UString("LZMAF86");
        case COMPRESSION_ALGORITHM_GZIP:                    return UString("GZip");
        case COMPRESSION_ALGORITHM_ZLIB:                    return UString("Zlib");
    }
    
    return usprintf("Unknown 0x%02X", algorithm);
}

UString actionTypeToUString(const UINT8 action)
{
    switch (action) {
        case Actions::NoAction:      return UString();
        case Actions::Create:        return UString("Create");
        case Actions::Insert:        return UString("Insert");
        case Actions::Replace:       return UString("Replace");
        case Actions::Remove:        return UString("Remove");
        case Actions::Rebuild:       return UString("Rebuild");
        case Actions::Rebase:        return UString("Rebase");
    }
    
    return usprintf("Unknown 0x%02X", action);
}

UString fitEntryTypeToUString(const UINT8 type)
{
    switch (type & 0x7F) {
        case INTEL_FIT_TYPE_HEADER:                     return UString("FIT Header");
        case INTEL_FIT_TYPE_MICROCODE:                  return UString("Microcode");
        case INTEL_FIT_TYPE_STARTUP_AC_MODULE:          return UString("Startup ACM");
        case INTEL_FIT_TYPE_DIAG_AC_MODULE:             return UString("Diagnostic ACM");
        case INTEL_FIT_TYPE_PLATFORM_BOOT_POLICY:       return UString("Platform Boot Policy");
        case INTEL_FIT_TYPE_FIT_RESET_STATE:            return UString("FIT Reset State");
        case INTEL_FIT_TYPE_BIOS_STARTUP_MODULE:        return UString("BIOS Startup Module");
        case INTEL_FIT_TYPE_TPM_POLICY:                 return UString("TPM Policy");
        case INTEL_FIT_TYPE_BIOS_POLICY:                return UString("BIOS Policy");
        case INTEL_FIT_TYPE_TXT_POLICY:                 return UString("TXT Policy");
        case INTEL_FIT_TYPE_BOOT_GUARD_KEY_MANIFEST:    return UString("BootGuard Key Manifest");
        case INTEL_FIT_TYPE_BOOT_GUARD_BOOT_POLICY:     return UString("BootGuard Boot Policy");
        case INTEL_FIT_TYPE_CSE_SECURE_BOOT:            return UString("CSE SecureBoot Settings");
        case INTEL_FIT_TYPE_VAB_PROVISIONING_TABLE:     return UString("VAB Provisioning Table");
        case INTEL_FIT_TYPE_VAB_KEY_MANIFEST:           return UString("VAB Key Manifest");
        case INTEL_FIT_TYPE_VAB_IMAGE_MANIFEST:         return UString("VAB Image Manifest");
        case INTEL_FIT_TYPE_VAB_IMAGE_HASH_DESCRIPTORS: return UString("VAB Image Hash Descriptors");
        case INTEL_FIT_TYPE_SACM_DEBUG_RECORD:          return UString("SACM Debug Record");
        case INTEL_FIT_TYPE_ACM_FEATURE_POLICY:         return UString("ACM Feature Policy");
        case INTEL_FIT_TYPE_SCRTM_ERROR_RECORD:         return UString("SCRTM Error Record");
        case INTEL_FIT_TYPE_JMP_DEBUG_POLICY:           return UString("JMP Debug Policy");
        case INTEL_FIT_TYPE_EMPTY:                      return UString("Empty");
    }
    
    return usprintf("Unknown 0x%02X", (type & 0x7F));
}

UString hashTypeToUString(const UINT16 algorithm_id)
{
    switch (algorithm_id) {
        case TCG_HASH_ALGORITHM_ID_SHA1:   return UString("SHA1");
        case TCG_HASH_ALGORITHM_ID_SHA256: return UString("SHA256");
        case TCG_HASH_ALGORITHM_ID_SHA384: return UString("SHA384");
        case TCG_HASH_ALGORITHM_ID_SHA512: return UString("SHA512");
        case TCG_HASH_ALGORITHM_ID_NULL:   return UString("NULL");
        case TCG_HASH_ALGORITHM_ID_SM3:    return UString("SM3");
    }
    
    return usprintf("Unknown 0x%04X", algorithm_id);
}

UString insydeFlashDeviceMapEntryTypeGuidToUString(const EFI_GUID & guid)
{
    const UByteArray baGuid((const char*)&guid, sizeof(EFI_GUID));
    if (baGuid == INSYDE_FLASH_MAP_REGION_BOOT_FV_GUID)          return UString("Boot Firmare Volume");
    if (baGuid == INSYDE_FLASH_MAP_REGION_BVDT_GUID)             return UString("BIOS Version Data Table");
    if (baGuid == INSYDE_FLASH_MAP_REGION_EC_GUID)               return UString("EC Firmware");
    if (baGuid == INSYDE_FLASH_MAP_REGION_FTW_BACKUP_GUID)       return UString("FTW Backup");
    if (baGuid == INSYDE_FLASH_MAP_REGION_FTW_STATE_GUID)        return UString("FTW State");
    if (baGuid == INSYDE_FLASH_MAP_REGION_FV_GUID)               return UString("Firmare Volume");
    if (baGuid == INSYDE_FLASH_MAP_REGION_FLASH_DEVICE_MAP_GUID) return UString("Flash Device Map");
    if (baGuid == INSYDE_FLASH_MAP_REGION_LOGO_GUID)             return UString("Logo");
    if (baGuid == INSYDE_FLASH_MAP_REGION_MICROCODE_GUID)        return UString("Microcode");
    if (baGuid == INSYDE_FLASH_MAP_REGION_MSDM_TABLE_GUID)       return UString("MSDM Table");
    if (baGuid == INSYDE_FLASH_MAP_REGION_MULTI_CONFIG_GUID)     return UString("MultiConfig");
    if (baGuid == INSYDE_FLASH_MAP_REGION_VAR_DEFAULT_GUID)      return UString("Variable Defaults");
    if (baGuid == INSYDE_FLASH_MAP_REGION_SMBIOS_UPDATE_GUID)    return UString("SMBIOS Update");
    if (baGuid == INSYDE_FLASH_MAP_REGION_VAR_GUID)              return UString("Variables");
    if (baGuid == INSYDE_FLASH_MAP_REGION_UNKNOWN_GUID)          return UString("Unknown");
    if (baGuid == INSYDE_FLASH_MAP_REGION_UNUSED_GUID)           return UString("Unused");
    if (baGuid == INSYDE_FLASH_MAP_REGION_USB_OPTION_ROM_GUID)   return UString("USB Option ROM");
    if (baGuid == INSYDE_FLASH_MAP_REGION_DXE_FV_GUID)           return UString("DXE Firmare Volume");
    if (baGuid == INSYDE_FLASH_MAP_REGION_PEI_FV_GUID)           return UString("PEI Firmare Volume");
    if (baGuid == INSYDE_FLASH_MAP_REGION_UNSIGNED_FV_GUID)      return UString("Unsigned Firmare Volume");
    return guidToUString(guid);
}
