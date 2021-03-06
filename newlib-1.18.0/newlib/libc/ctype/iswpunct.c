/* Copyright (c) 2002 Red Hat Incorporated.
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

     Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

     Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.

     The name of Red Hat Incorporated may not be used to endorse
     or promote products derived from this software without specific
     prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED.  IN NO EVENT SHALL RED HAT INCORPORATED BE LIABLE FOR ANY
   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS   
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
FUNCTION
	<<iswpunct>>---punctuation wide character test

INDEX
	iswpunct

ANSI_SYNOPSIS
	#include <wctype.h>
	int iswpunct(wint_t <[c]>);

TRAD_SYNOPSIS
	#include <wctype.h>
	int iswpunct(<[c]>)
	wint_t <[c]>;

DESCRIPTION
<<iswpunct>> is a function which classifies wide-character values that
are punctuation.

RETURNS
<<iswpunct>> returns non-zero if <[c]> is a punctuation wide character.

PORTABILITY
<<iswpunct>> is C99.

No supporting OS subroutines are required.
*/
#include <_ansi.h>
#include <newlib.h>
#include <wctype.h>
#include <string.h>
#include <ctype.h>
#include "local.h"

#ifdef _MB_CAPABLE
#include "utf8punct.h"
#endif /* _MB_CAPABLE */

int
_DEFUN(iswpunct,(c), wint_t c)
{
#ifdef _MB_CAPABLE
  unsigned const char *table;
  unsigned char *ptr;
  unsigned char ctmp;
  int size;
  wint_t x;

  c = _jp2uc (c);

  x = (c >> 8);
  /* for some large sections, all characters are punctuation so handle them here */
  if ((x >= 0xe0 && x <= 0xf8) ||
      (x >= 0xf00 && x <= 0xffe) ||
      (x >= 0x1000 && x <= 0x10fe))
    return 1;
  
  switch (x)
    {
    case 0x22:
    case 0x25:
    case 0x28:
    case 0x29:
    case 0x2a:
      return 1;
    case 0x00:
      table = u0;
      size = sizeof(u0);
      break;
    case 0x02:
      table = u2;
      size = sizeof(u2);
      break;
    case 0x03:
      table = u3;
      size = sizeof(u3);
      break;
    case 0x04:
      table = u4;
      size = sizeof(u4);
      break;
    case 0x05:
      table = u5;
      size = sizeof(u5);
      break;
    case 0x06:
      table = u6;
      size = sizeof(u6);
      break;
    case 0x07:
      table = u7;
      size = sizeof(u7);
      break;
    case 0x09:
      table = u9;
      size = sizeof(u9);
      break;
    case 0x0a:
      table = ua;
      size = sizeof(ua);
      break;
    case 0x0b:
      table = ub;
      size = sizeof(ub);
      break;
    case 0x0c:
      table = uc;
      size = sizeof(uc);
      break;
    case 0x0d:
      table = ud;
      size = sizeof(ud);
      break;
    case 0x0e:
      table = ue;
      size = sizeof(ue);
      break;
    case 0x0f:
      table = uf;
      size = sizeof(uf);
      break;
    case 0x10:
      table = u10;
      size = sizeof(u10);
      break;
    case 0x13:
      table = u13;
      size = sizeof(u13);
      break;
    case 0x16:
      table = u16;
      size = sizeof(u16);
      break;
    case 0x17:
      table = u17;
      size = sizeof(u17);
      break;
    case 0x18:
      table = u18;
      size = sizeof(u18);
      break;
    case 0x1f:
      table = u1f;
      size = sizeof(u1f);
      break;
    case 0x20:
      table = u20;
      size = sizeof(u20);
      break;
    case 0x21:
      table = u21;
      size = sizeof(u21);
      break;
    case 0x23:
      table = u23;
      size = sizeof(u23);
      break;
    case 0x24:
      table = u24;
      size = sizeof(u24);
      break;
    case 0x26:
      table = u26;
      size = sizeof(u26);
      break;
    case 0x27:
      table = u27;
      size = sizeof(u27);
      break;
    case 0x2e:
      table = u2e;
      size = sizeof(u2e);
      break;
    case 0x2f:
      table = u2f;
      size = sizeof(u2f);
      break;
    case 0x30:
      table = u30;
      size = sizeof(u30);
      break;
    case 0x31:
      table = u31;
      size = sizeof(u31);
      break;
    case 0x32:
      table = u32;
      size = sizeof(u32);
      break;
    case 0x33:
      table = u33;
      size = sizeof(u33);
      break;
    case 0xa4:
      table = ua4;
      size = sizeof(ua4);
      break;
    case 0xfb:
      table = ufb;
      size = sizeof(ufb);
      break;
    case 0xfd:
      table = ufd;
      size = sizeof(ufd);
      break;
    case 0xfe:
      table = ufe;
      size = sizeof(ufe);
      break;
    case 0xff:
      table = uff;
      size = sizeof(uff);
      break;
    case 0x103:
      table = u103;
      size = sizeof(u103);
      break;
    case 0x1d0:
      table = u1d0;
      size = sizeof(u1d0);
      break;
    case 0x1d1:
      table = u1d1;
      size = sizeof(u1d1);
      break;
    case 0x1d6:
      table = u1d6;
      size = sizeof(u1d6);
      break;
    case 0x1d7:
      table = u1d7;
      size = sizeof(u1d7);
      break;
    case 0xe00:
      table = ue00;
      size = sizeof(ue00);
      break;
    case 0xfff:
      table = ufff;
      size = sizeof(ufff);
      break;
    case 0x10ff:
      table = u10ff;
      size = sizeof(u10ff);
      break;
    default:
      return 0;
    }
  /* we have narrowed down to a section of 256 characters to check */
  /* now check if c matches the punctuation wide-chars within that section */
  ptr = (unsigned char *)table;
  ctmp = (unsigned char)c;
  while (ptr < table + size)
    {
      if (ctmp == *ptr)
	return 1;
      if (ctmp < *ptr)
	return 0;
      /* otherwise c > *ptr */
      /* look for 0x0 as next element which indicates a range */
      ++ptr;
      if (*ptr == 0x0)
	{
	  /* we have a range..see if c falls within range */
	  ++ptr;
	  if (ctmp <= *ptr)
	    return 1;
	  ++ptr;
	}
    }
  /* not in table */
  return 0;
#else
  return (c < (wint_t)0x100 ? ispunct (c) : 0);
#endif /* _MB_CAPABLE */
}

