// mnml-as - Assembler for the mnml-vm virtual stack machine.
// Copyright (C) 2023  Mathias Hörtnagl <mathias.hoertnagl[ÄT]gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef VM_H
#define VM_H

// clang-format off
#define VM_PSH 0x00 // (       -- a              )
#define VM_POP 0x01 // ( a     --                )
#define VM_NIP 0x02 // ( a b   -- a              )
#define VM_SWP 0x03 // ( a b   -- b a            )
#define VM_OVR 0x04 // ( a b   -- b a b          )
#define VM_DUP 0x05 // ( a     -- a a            )
#define VM_ROT 0x06 // ( a b c -- b c a          )
#define VM_INC 0x07 // ( a     -- a+1            )
#define VM_DEC 0x08 // ( a     -- a-1            )
#define VM_ADD 0x09 // ( a b   -- b+a            )
#define VM_SUB 0x0a // ( a b   -- b-a            )
#define VM_MUL 0x0b // ( a b   -- b*a            )
#define VM_DIV 0x0c // ( a b   -- ⌊b/a⌋          )
#define VM_NOT 0x0d // ( a     -- !a             )
#define VM_AND 0x0e // ( a b   -- b&a            )
#define VM_OOR 0x0f // ( a b   -- b|a            )
#define VM_XOR 0x10 // ( a b   -- b^a            )
#define VM_SLL 0x11 // ( a b   -- b<<a           )
#define VM_SRL 0x12 // ( a b   -- b>>a           )
#define VM_EQU 0x13 // ( a b   -- b==a?1:0       )
#define VM_NEQ 0x14 // ( a b   -- b!=a?1:0       )
#define VM_SLT 0x15 // ( a b   -- b<a            )
#define VM_SGT 0x16 // ( a b   -- b>a            )
#define VM_SLE 0x17 // ( a b   -- b<=a           )
#define VM_SGE 0x18 // ( a b   -- b>=a           )
#define VM_JMP 0x19 // ( a     --                ) pc = a
#define VM_JAL 0x1a // ( a     -- pc+1           ) pc = a
#define VM_BRA 0x1b // ( b a   --                ) if b then pc = a
#define VM_LDW 0x1c // ( a     -- mem[a]         )
#define VM_STW 0x1d // ( a b   --                ) mem[a] = b
#define VM_DRX 0x1e // ( a b   -- dev[b].read(a) )
#define VM_DTX 0x1f // ( a b c --                ) dev[b].write(a, c)

// SIDE EFFECTS
// ------------------------------------------
// VM_PSH - Pushes the next two bytes in the 
//          binary onto the stack.
// VM_JMP - Sets the program counter to the 
//          top of the stack.
// VM_JAL - Sets the program counter to the 
//          top of the stack.
// VM_BRA - Sets the program counter to the 
//          second element on the stack if
//          the top element evaluates to 1.
// VM_STW - Stores the second element in 
//          memory at the address specified
//          by the top element on the stack.
// VM_DTX - Writes the third element on the
//          stack to the memory address of 
//          the top element of the device 
//          identified by the second element.
// clang-format on

#endif