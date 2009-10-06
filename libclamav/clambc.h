/*
 *  ClamAV bytecode definitions.
 *
 *  Copyright (C) 2009 Sourcefire, Inc.
 *
 *  Authors: Török Edvin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 */
#ifndef CLAMBC_H
#define CLAMBC_H


struct bytecode_metadata {
  unsigned long maxStack, maxMem;
  unsigned long maxTime;
  char *targetExclude;
};

#define BC_FUNC_LEVEL 1
#define BC_HEADER "ClamBC"

enum bc_opcode {
  OP_BC_ADD=1,
  OP_BC_SUB,
  OP_BC_MUL,
  OP_BC_UDIV,
  OP_BC_SDIV,
  OP_BC_UREM,
  OP_BC_SREM,
  OP_BC_SHL,
  OP_BC_LSHR,
  OP_BC_ASHR,
  OP_BC_AND,
  OP_BC_OR,
  OP_BC_XOR,

  OP_BC_TRUNC,
  OP_BC_SEXT,
  OP_BC_ZEXT,

  OP_BC_BRANCH,
  OP_BC_JMP,
  OP_BC_RET,
  OP_BC_RET_VOID,

  OP_BC_ICMP_EQ,
  OP_BC_ICMP_NE,
  OP_BC_ICMP_UGT,
  OP_BC_ICMP_UGE,
  OP_BC_ICMP_ULT,
  OP_BC_ICMP_ULE,
  OP_BC_ICMP_SGT,
  OP_BC_ICMP_SGE,
  OP_BC_ICMP_SLE,
  OP_BC_ICMP_SLT,
  OP_BC_SELECT,
  OP_BC_CALL_DIRECT,
  OP_BC_CALL_API,
  OP_BC_COPY,
  OP_BC_GEP1,
  OP_BC_GEP2,
  OP_BC_GEPN,
  OP_BC_STORE,
  OP_BC_LOAD,
  OP_BC_INVALID /* last */
};

static const unsigned char operand_counts[] = {
  0,
  /* ADD -> XOR */
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  /* TRUNC -> ZEXT */
  1, 1, 1,
  /* BRANCH, JMP, RET */
  3, 1, 1, 0,
  /* ICMP */
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
  /* SELECT */
  3,
  /* CALLs have variable number of operands */
  0, 0,
  /* OP_BC_COPY */
  2,
  /* OP_BC_GEP1, OP_BC_GEP2, OP_BC_GEPN, OP_BC_STORE, OP_BC_LOAD*/
  2, 3, 0, 2, 1
};

enum bc_global {
  _FIRST_GLOBAL = 0x8000,
  GLOBAL_MATCH_COUNTS = 0x8000,
  GLOBAL_KIND,
  GLOBAL_VIRUSNAMES,
  GLOBAL_EXEINFO,
  _LAST_GLOBAL
};

#define BC_START_TID 69
#endif