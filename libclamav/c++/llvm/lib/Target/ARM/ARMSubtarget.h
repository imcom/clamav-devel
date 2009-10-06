//=====---- ARMSubtarget.h - Define Subtarget for the ARM -----*- C++ -*--====//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the ARM specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#ifndef ARMSUBTARGET_H
#define ARMSUBTARGET_H

#include "llvm/Target/TargetInstrItineraries.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetSubtarget.h"
#include <string>

namespace llvm {
class GlobalValue;

class ARMSubtarget : public TargetSubtarget {
protected:
  enum ARMArchEnum {
    V4T, V5T, V5TE, V6, V6T2, V7A
  };

  enum ARMFPEnum {
    None, VFPv2, VFPv3, NEON
  };

  enum ThumbTypeEnum {
    Thumb1,
    Thumb2
  };

  /// ARMArchVersion - ARM architecture version: V4T (base), V5T, V5TE,
  /// V6, V6T2, V7A.
  ARMArchEnum ARMArchVersion;

  /// ARMFPUType - Floating Point Unit type.
  ARMFPEnum ARMFPUType;

  /// UseNEONForSinglePrecisionFP - if the NEONFP attribute has been
  /// specified. Use the method useNEONForSinglePrecisionFP() to
  /// determine if NEON should actually be used.
  bool UseNEONForSinglePrecisionFP;

  /// IsThumb - True if we are in thumb mode, false if in ARM mode.
  bool IsThumb;

  /// ThumbMode - Indicates supported Thumb version.
  ThumbTypeEnum ThumbMode;

  /// PostRAScheduler - True if using post-register-allocation scheduler.
  bool PostRAScheduler;

  /// IsR9Reserved - True if R9 is a not available as general purpose register.
  bool IsR9Reserved;

  /// stackAlignment - The minimum alignment known to hold of the stack frame on
  /// entry to the function and which must be maintained by every function.
  unsigned stackAlignment;

  /// CPUString - String name of used CPU.
  std::string CPUString;

  /// Selected instruction itineraries (one entry per itinerary class.)
  InstrItineraryData InstrItins;

 public:
  enum {
    isELF, isDarwin
  } TargetType;

  enum {
    ARM_ABI_APCS,
    ARM_ABI_AAPCS // ARM EABI
  } TargetABI;

  /// This constructor initializes the data members to match that
  /// of the specified triple.
  ///
  ARMSubtarget(const std::string &TT, const std::string &FS, bool isThumb);

  /// getMaxInlineSizeThreshold - Returns the maximum memset / memcpy size
  /// that still makes it profitable to inline the call.
  unsigned getMaxInlineSizeThreshold() const {
    // FIXME: For now, we don't lower memcpy's to loads / stores for Thumb.
    // Change this once Thumb ldmia / stmia support is added.
    return isThumb() ? 0 : 64;
  }
  /// ParseSubtargetFeatures - Parses features string setting specified
  /// subtarget options.  Definition of function is auto generated by tblgen.
  std::string ParseSubtargetFeatures(const std::string &FS,
                                     const std::string &CPU);

  bool hasV4TOps()  const { return ARMArchVersion >= V4T;  }
  bool hasV5TOps()  const { return ARMArchVersion >= V5T;  }
  bool hasV5TEOps() const { return ARMArchVersion >= V5TE; }
  bool hasV6Ops()   const { return ARMArchVersion >= V6;   }
  bool hasV6T2Ops() const { return ARMArchVersion >= V6T2; }
  bool hasV7Ops()   const { return ARMArchVersion >= V7A;  }

  bool hasVFP2() const { return ARMFPUType >= VFPv2; }
  bool hasVFP3() const { return ARMFPUType >= VFPv3; }
  bool hasNEON() const { return ARMFPUType >= NEON;  }
  bool useNEONForSinglePrecisionFP() const {
    return hasNEON() && UseNEONForSinglePrecisionFP; }

  bool isTargetDarwin() const { return TargetType == isDarwin; }
  bool isTargetELF() const { return TargetType == isELF; }

  bool isAPCS_ABI() const { return TargetABI == ARM_ABI_APCS; }
  bool isAAPCS_ABI() const { return TargetABI == ARM_ABI_AAPCS; }

  bool isThumb() const { return IsThumb; }
  bool isThumb1Only() const { return IsThumb && (ThumbMode == Thumb1); }
  bool isThumb2() const { return IsThumb && (ThumbMode == Thumb2); }
  bool hasThumb2() const { return ThumbMode >= Thumb2; }

  bool isR9Reserved() const { return IsR9Reserved; }

  const std::string & getCPUString() const { return CPUString; }
  
  /// enablePostRAScheduler - From TargetSubtarget, return true to
  /// enable post-RA scheduler.
  bool enablePostRAScheduler() const { return PostRAScheduler; }

  /// getInstrItins - Return the instruction itineraies based on subtarget
  /// selection.
  const InstrItineraryData &getInstrItineraryData() const { return InstrItins; }

  /// getStackAlignment - Returns the minimum alignment known to hold of the
  /// stack frame on entry to the function and which must be maintained by every
  /// function for this subtarget.
  unsigned getStackAlignment() const { return stackAlignment; }

  /// GVIsIndirectSymbol - true if the GV will be accessed via an indirect
  /// symbol.
  bool GVIsIndirectSymbol(GlobalValue *GV, Reloc::Model RelocM) const;
};
} // End llvm namespace

#endif  // ARMSUBTARGET_H