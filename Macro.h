//
// Created by wil98 on 2017-06-14.
//

#ifndef PPM_MACRO_H
#define PPM_MACRO_H

#define WRITE_TO_FILE(x, f) fwrite(x, sizeof(char), strlen(x), f)
#define PRINT_8_HEX(x) printf("0x%08x\n", (int)x);

#define MAX2(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) (MAX2(MAX2(a, b), c))
#define MIN2(a, b) ((a) < (b) ? (a) : (b))
#define MIN3(a, b, c) (MIN2(MIN2(a, b), c))

#endif //PPM_MACRO_H
