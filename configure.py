#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "GSNE8P",  # 0
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--ninja",
    metavar="BINARY",
    type=Path,
    help="path to ninja binary (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--warn",
    dest="warn",
    type=str,
    choices=["all", "off", "error"],
    help="how to handle warnings",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-2"
config.compilers_tag = "20251118"
config.dtk_tag = "v1.8.3"
config.objdiff_tag = "v3.6.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.3"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    "-multibyte",  # For Wii compilers, replace with `-enc SJIS`
    "-i include",
    "-i include/stl",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
    f"-DDTK_CONFIG_NONMATCHING={config.non_matching:d}",
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Warning flags
if args.warn == "all":
    cflags_base.append("-W all")
elif args.warn == "off":
    cflags_base.append("-W off")
elif args.warn == "error":
    cflags_base.append("-W error")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    # "-gccinc",
    "-common off",
    "-inline auto",
]

cflags_dol = [
    *cflags_base,
    "-opt nopeep",
    "-opt noschedule",
    "-pool off",
    "-inline off",
    # "-inline deferred",
    "-fp_contract off",
    "-use_lmw_stmw off",
    "-sym on"
]

# REL flags
cflags_rel = [
    *cflags_base,
    "-sdata 0",
    "-sdata2 0",
    "-opt nopeep",
    "-opt noschedule",
    "-pool off",
    "-inline off",
    # "-inline deferred",
    "-fp_contract off",
    "-use_lmw_stmw off",
    "-sym on"
]

config.linker_version = "GC/1.3.2"


# Helper function for Dolphin libraries
def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    mw_version = "GC/1.2.5"
    if lib_name in {"pad", "card", "hio", "OdemuExi2", "mtx"}:
        mw_version = "GC/1.2.5n"
    # if version_num in (6, 7) or (lib_name in ("card", "hio", "pad") and version_num == 3) or (lib_name in ("mtx", "pad", "vi") and version_num == 0):  # JPN demo, PAL, and SOMETIMES USA demo
    return {
        "lib": lib_name,
        "mw_version": mw_version,
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": objects,
    }


# Helper function for REL script objects
def Rel(lib_name: str, objects: List[Object], **kwargs) -> Dict[str, Any]:
    flags = cflags_rel
    if "extra_cflags" in kwargs:
        flags = cflags_rel + kwargs["extra_cflags"]
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5",
        "cflags": flags,
        "progress_category": "game",
        "objects": objects,
    }
def ChaoRel(lib_name: str, objects: List[Object], **kwargs) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_rel + [
            "-inline deferred",
            "-opt schedule",
            "-opt peep",
            "-pool on",
            "-use_lmw_stmw on",
        ],
        "progress_category": "game",
        "objects": objects,
    }


Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False

CHAOPIPE_C = Object(Matching, "OBJECT/o_chaopipe.c")
SPRING_C = Object(Matching, "OBJECT/o_spring.c")
RING_C = Object(NonMatching, "OBJECT/o_ring.c")

config.libs = [
    DolphinLib(
        "base",
        [
            Object(Matching, "Dolphin/base/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "os",
        [
            Object(Matching, "Dolphin/os/OS.c"),
            Object(Matching, "Dolphin/os/OSAlarm.c"),
            Object(Matching, "Dolphin/os/OSAlloc.c"),
            Object(Matching, "Dolphin/os/OSArena.c"),
            Object(Matching, "Dolphin/os/OSAudioSystem.c"),
            Object(Matching, "Dolphin/os/OSCache.c"),
            Object(Matching, "Dolphin/os/OSContext.c"),
            Object(Matching, "Dolphin/os/OSError.c"),
            Object(Matching, "Dolphin/os/OSExi.c"),
            Object(Matching, "Dolphin/os/OSFont.c"),
            Object(Matching, "Dolphin/os/OSInterrupt.c"),
            Object(Matching, "Dolphin/os/OSLink.c"),
            Object(Matching, "Dolphin/os/OSMemory.c"),
            Object(Matching, "Dolphin/os/OSMutex.c"),
            Object(Matching, "Dolphin/os/OSReboot.c"),
            Object(Matching, "Dolphin/os/OSReset.c"),
            Object(Matching, "Dolphin/os/OSResetSW.c"),
            Object(Matching, "Dolphin/os/OSRtc.c"),
            Object(Matching, "Dolphin/os/OSSerial.c"),
            Object(Matching, "Dolphin/os/OSSync.c"),
            Object(Matching, "Dolphin/os/OSThread.c"),
            Object(Matching, "Dolphin/os/OSTime.c"),
            Object(Matching, "Dolphin/os/OSUartExi.c"),
            Object(Matching, "Dolphin/os/__start.c"),
            Object(Matching, "Dolphin/os/__ppc_eabi_init.cpp"),
        ],
    ),
    DolphinLib(
        "db",
        [
            Object(Matching, "db/db.c"),
        ],
    ),
    DolphinLib(
        "OdemuExi2",
        [
            Object(Matching, "Dolphin/OdemuExi2/DebuggerDriver.c", extra_cflags=["-inline deferred"]),
        ],
    ),
    DolphinLib(
        "odenotstub",
        [
            Object(Matching, "Dolphin/odenotstub/odenotstub.c"),
        ],
    ),
    DolphinLib(
        "mtx",
        [
            Object(Matching, "Dolphin/mtx/mtx.c", extra_cflags=["-fp_contract off"]),
            Object(Matching, "Dolphin/mtx/mtxvec.c"),
            Object(Matching, "Dolphin/mtx/mtx44.c"),
            Object(Matching, "Dolphin/mtx/vec.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            Object(Matching, "Dolphin/dvd/dvdlow.c"),
            Object(Matching, "Dolphin/dvd/dvdfs.c", extra_cflags=["-char signed"]),
            Object(Matching, "Dolphin/dvd/dvd.c"),
            Object(Matching, "Dolphin/dvd/dvdqueue.c"),
            Object(Matching, "Dolphin/dvd/dvderror.c"),
            Object(Matching, "Dolphin/dvd/fstload.c", extra_cflags=["-char signed" if version_num in (0, 3, 6, 7) else "-char unsigned"]),
        ],
    ),
    DolphinLib(
        "vi",
        [
            Object(Matching, "Dolphin/vi/vi.c"),
        ],
    ),
    DolphinLib(
        "pad",
        [
            Object(Matching, "Dolphin/pad/Padclamp.c"),
            Object(Matching, "Dolphin/pad/Pad.c"),
        ],
    ),
    DolphinLib(
        "ai",
        [
            Object(Matching, "Dolphin/ai/ai.c"),
        ],
    ),
    DolphinLib(
        "ax",
        [
            Object(Matching, "Dolphin/ax/AX.c"),
            Object(Matching, "Dolphin/ax/AXAlloc.c"),
            Object(Matching, "Dolphin/ax/AXAux.c"),
            Object(Matching, "Dolphin/ax/AXCL.c"),
            Object(NonMatching, "Dolphin/ax/AXOut.c"),
            Object(Matching, "Dolphin/ax/AXProf.c"),
            Object(Matching, "Dolphin/ax/AXSPB.c"),
            Object(NonMatching, "Dolphin/ax/AXVPB.c"),
            Object(Matching, "Dolphin/ax/DSPCode.c"),
        ],
    ),
        DolphinLib(
        "mix",
        [
            Object(NonMatching, "Dolphin/mix/mix.c"),
        ],
    ),
    DolphinLib(
        "axfx",
        [
            Object(Matching, "Dolphin/axfx/axfx.c"),
            Object(Matching, "Dolphin/axfx/chorus.c"),
            Object(Matching, "Dolphin/axfx/delay.c"),
            Object(Matching, "Dolphin/axfx/reverb_hi.c", extra_cflags=["-fp_contract off"]),
            # Object(NonMatching, "Dolphin/axfx/reverb_hi_4ch.c"),
            Object(Matching, "Dolphin/axfx/reverb_std.c", extra_cflags=["-fp_contract off"]),
        ],
    ),
    DolphinLib(
        "ar",
        [
            Object(Matching, "Dolphin/ar/ar.c"),
            Object(Matching, "Dolphin/ar/arq.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            Object(Matching, "Dolphin/dsp/dsp.c"),
            Object(Matching, "Dolphin/dsp/dsp_debug.c"),
            Object(Matching, "Dolphin/dsp/dsp_task.c"),
        ],
    ),
    DolphinLib(
        "card",
        [
            Object(Matching, "Dolphin/card/CARDBios.c"),
            Object(Matching, "Dolphin/card/CARDUnlock.c"),
            Object(Matching, "Dolphin/card/CARDRdwr.c"),
            Object(Matching, "Dolphin/card/CARDBlock.c"),
            Object(Matching, "Dolphin/card/CARDDir.c"),
            Object(Matching, "Dolphin/card/CARDCheck.c"),
            Object(Matching, "Dolphin/card/CARDMount.c"),
            Object(Matching, "Dolphin/card/CARDFormat.c"),
            Object(Matching, "Dolphin/card/CARDOpen.c"),
            Object(Matching, "Dolphin/card/CARDCreate.c"),
            Object(Matching, "Dolphin/card/CARDRead.c"),
            Object(Matching, "Dolphin/card/CARDWrite.c"),
            Object(Matching, "Dolphin/card/CARDDelete.c"),
            Object(Matching, "Dolphin/card/CARDStat.c"),
            Object(Matching, "Dolphin/card/CARDStatEX.c"),
            Object(Matching, "Dolphin/card/CARDNet.c"),
        ],
    ),
    # DolphinLib(
    #     "si",
    #     [
    #         Object(NonMatching, "Dolphin/si/SIBios.c"),
    #         Object(NonMatching, "Dolphin/si/SISamplingRate.c"),
    #     ],
    # ),
    # DolphinLib(
    #     "exi",
    #     [
    #         Object(NonMatching, "Dolphin/exi/EXIBios.c"),
    #         Object(NonMatching, "Dolphin/exi/EXIUart.c"),
    #     ],
    # ),
    DolphinLib(
        "hio",
        [
            Object(NonMatching, "Dolphin/hio/hio.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(Matching, "Dolphin/gx/GXInit.c"),
            Object(Matching, "Dolphin/gx/GXFifo.c"),
            Object(Matching, "Dolphin/gx/GXAttr.c"),
            Object(Matching, "Dolphin/gx/GXMisc.c"),
            Object(Matching, "Dolphin/gx/GXGeometry.c"),
            Object(Matching, "Dolphin/gx/GXFrameBuf.c"),
            Object(Matching, "Dolphin/gx/GXLight.c"),
            Object(Matching, "Dolphin/gx/GXTexture.c"),
            Object(Matching, "Dolphin/gx/GXBump.c"),
            Object(Matching, "Dolphin/gx/GXTev.c"),
            Object(Matching, "Dolphin/gx/GXPixel.c"),
            Object(Matching, "Dolphin/gx/GXStubs.c"),
            Object(Matching, "Dolphin/gx/GXDisplayList.c"),
            Object(Matching, "Dolphin/gx/GXTransform.c", extra_cflags=["-fp_contract off"]),
            Object(Matching, "Dolphin/gx/GXPerf.c"),
        ],
    ),
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": "GC/1.2.5",
        "progress_category": "sdk",
        "cflags": [*cflags_runtime, "-inline deferred"],
        "objects": [
            Object(Matching, "Dolphin/Runtime/PPCEABI/H/__mem.c"),
            Object(Matching, "Dolphin/Runtime/PPCEABI/H/__va_arg.c"),
            Object(Matching, "Dolphin/Runtime/PPCEABI/H/global_destructor_chain.c"),
            # Object(NonMatching, "Dolphin/Runtime/PPCEABI/H/CPlusLibPPC.cp"),
            # Object(NonMatching, "Dolphin/Runtime/PPCEABI/H/NMWException.cp"),
            # Object(NonMatching, "Dolphin/Runtime/PPCEABI/H/ptmf.c"),
            # Object(NonMatching, "Dolphin/Runtime/PPCEABI/H/ExceptionPPC.cp"),
            Object(Matching, "Dolphin/Runtime/PPCEABI/H/runtime.c"),
            # Object(NonMatching, "Dolphin/Runtime/PPCEABI/H/__init_cpp_exceptions.cpp"),
        ],
    },
    {
        "lib": "MSL_C.PPCEABI.bare.H",
        "mw_version": "GC/1.2.5",
        "progress_category": "sdk",
        "cflags": [
            *cflags_base,
            "-fp_contract on",
            "-inline auto,deferred",
            "-str pool,readonly",
        ],
        "objects": [
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/ansi_files.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/abort_exit.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/errno.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/ansi_fp.c"),
            # Object(NonMatching, "Dolphin/MSL_C/PPCEABI/bare/H/arith.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/buffer_io.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/critical_regions.ppc_eabi.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/ctype.c"),
            # Object(NonMatching, "Dolphin/MSL_C/PPCEABI/bare/H/locale.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/direct_io.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/mbstring.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/mem.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/mem_funcs.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/misc_io.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/printf.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/rand.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/scanf.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/string.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/strtoul.c"),
            # Object(NonMatching, "Dolphin/MSL_C/PPCEABI/bare/H/strtold.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/uart_console_io.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/wchar_io.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/float.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/e_asin.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/e_log.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/e_log10.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/e_rem_pio2.c"),
            # Object(NonMatching, "Dolphin/MSL_C/PPCEABI/bare/H/e_atan2.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/e_pow.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/fminmaxdim.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/k_cos.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/k_rem_pio2.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/k_sin.c"),
            # Object(NonMatching, "Dolphin/MSL_C/PPCEABI/bare/H/s_atan.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/s_copysign.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/s_cos.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/s_floor.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/s_frexp.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/s_ldexp.c"),
            # Object(NonMatching, "Dolphin/MSL_C/PPCEABI/bare/H/w_atan2.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/w_log.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/w_log10.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/w_pow.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/hyperbolicsf.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/inverse_trig.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/ceilfloor.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/trigf.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/math_inlines.c"),
            Object(NonMatching, "Dolphin/MSL_C/PPCEABI/bare/H/powf.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/logf.c"),
            Object(Matching, "Dolphin/MSL_C/PPCEABI/bare/H/common_float_tables.c"),
        ],
    },
    {
        "lib": "TRK_MINNOW_DOLPHIN",
        "mw_version": "GC/1.1p1",
        "progress_category": "sdk",
        "cflags": [
            *cflags_runtime,
            "-rostr",
            "-sdata 0",
            "-sdata2 0",
            "-pool off",
            "-inline on,noauto",
        ],
        "objects": [
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/mainloop.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/nubevent.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/nubinit.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/msg.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/msgbuf.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/serpoll.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/usr_put.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/dispatch.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/msghndlr.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/support.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/mutex_TRK.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/notify.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/flush_cache.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/mem_TRK.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/__exception.s"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/targimpl.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/dolphin_trk.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/mpc_7xx_603e.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/main_TRK.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/dolphin_trk_glue.c"),
            Object(Matching, "Dolphin/TRK_MINNOW_DOLPHIN/targcont.c"),
        ],
    },
    {
        "lib": "Ninja",
        "mw_version": "GC/1.2.5",
        "cflags": cflags_dol,
        "objects": [
            Object(Matching, "Ninja/njCubicBezier.c"),
            Object(Matching, "Ninja/njFraction.c"),
            Object(Matching, "Ninja/njRoundOff.c"),
            Object(Matching, "Ninja/njRoundUp.c"),
            Object(Matching, "Ninja/njSinCos.c"),
        ],
    },
    Rel(
        "stg13D",
        [
            Object(Matching, "stg13_cityescape/o_ce_adx_chg.c"),
            Object(Matching, "stg13_cityescape/o_ce_board.c"),
            Object(Matching, "stg13_cityescape/o_ce_board_col.c"),
            Object(NonMatching, "stg13_cityescape/o_ce_sobj.c"),
            CHAOPIPE_C,
            SPRING_C,
            RING_C,
        ]
    ),
    ChaoRel(
        "ChaoMain",
        [
            Object(NonMatching, "chao/al_face.c"),
            Object(NonMatching, "chao/al_garden_info.c"),
            Object(Matching, "chao/al_gene.c"),
        ]
    )
]


# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects


# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("sdk", "SDK Code"),
]
config.progress_each_module = args.verbose
# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    # Marks relocations as mismatching if the target value is different
    # Default is "functionRelocDiffs=none", which is most lenient
    # "--config functionRelocDiffs=data_value",
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
