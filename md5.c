/* Simple MD5 implementation
 * Can be run or compiled with: gcc -o md5 -O3 -lm md5.c
 */
 //Hassan Mahmood
 //LAB SECTION 30
 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
 
// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
 // These vars will contain the hash
uint32_t h0, h1, h2, h3;
//function md5 require the address of your raw message
// and the length of your message
// Variable h0, h1, h2, h3 will contain the hash output
// h0, h1, h2, h3 are global variable available to all functions in code
void md5(uint8_t *initial_msg, size_t initial_len) {
    // Message (to prepare)
    uint8_t *msg = NULL;
    // Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating
    // r specifies the per-round shift amounts
 
    uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    // Use binary integer part of the sines of integers (in radians) as constants// Initialize variables:
    uint32_t k[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
 
    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;
 
    // Pre-processing: adding a single 1 bit
    //append "1" bit to message    
    /* Notice: the input bytes are considered as bits strings,
       where the first bit is the most significant bit of the byte.[37] */
 
    // Pre-processing: padding with zeros
    //append "0" bit until message length in bit ≡ 448 (mod 512)
    //append length mod (2 pow 64) to message
 
    int new_len;
    for(new_len = initial_len*8 + 1; new_len%512!=448; new_len++);
    new_len /= 8;
 
    msg = calloc(new_len + 64, 1); // also appends "0" bits 
                                   // (we alloc also 64 extra bytes...)
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128; // write the "1" bit
 
    uint32_t bits_len = 8*initial_len; // note, we append the len
    memcpy(msg + new_len, &bits_len, 4);           // in bits at the end of the buffer
 
    // Process the message in successive 512-bit chunks:
    //for each 512-bit chunk of message:
    int offset;
    for(offset=0; offset<new_len; offset += (512/8)) {
 
        // break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
        uint32_t *w = (uint32_t *) (msg + offset);
 
        // Initialize hash value for this chunk:
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        
        
 
        // Main loop:
        uint32_t i;
        for(i = 0; i<64; i++) {
            uint32_t f, g;
 
             if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;          
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }

            uint32_t temp = d;
            d = c;
            c = b;
            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
            a = temp;
        }
        // Add this chunk's hash to result so far:
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
    }
    // cleanup
    free(msg);
}
 
int main() {
    
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz"; //continue to z
    int nc = strlen(alphabet);

 	char string1[]="bbb"; //do not assign size to make it variable
 	uint8_t *p8;
    size_t len = strlen(string1);
    for (int k=0; k<nc; k++)
    {
        for (int l=0; l<nc; l++)
        {
            for (int h=0; h<nc;h++)
            {
            string1[0] = alphabet[k];
            string1[1] = alphabet[l];
            string1[2] = alphabet[h];
            
            printf("string =%s hash =",string1);
            md5(string1, len);
            p8=(uint8_t *)&h0;
            printf("%02x%02x%02x%02x", *p8, *(p8+1), *(p8+2), *(p8+3));
            p8=(uint8_t *)&h1;
            printf("%02x%02x%02x%02x", p8[0], p8[1], p8[2], p8[3]);
            p8=(uint8_t *)&h2;
            printf("%02x%02x%02x%02x", p8[0], p8[1], p8[2], p8[3]);
            p8=(uint8_t *)&h3;
            printf("%02x%02x%02x%02x", p8[0], p8[1], p8[2], p8[3]);
            printf("\n");
            }     
        }
    }

//comparison of the last hash 
//(example is only for h0, extend it to h1, h2, h3)
//(after running the for loop the only hash stored is the last one for "dd")
//md5 for "dd" is 1aabac6d068eef6a7bad3fdf50a05cc8
//print h0 from our md5 function to check its contents
printf("h0 = %08x", h0);
//Notice that h0 start with the least significant digits
p8=(uint8_t *)&h0;

//load the hash value to unhash in pieces:
uint32_t tounhash0 = 0x1aabac6d;
uint8_t * p8hash;
p8hash=(uint8_t *)&tounhash0;
_Bool pflag = 0;
//uint32_t tounhash1 = 0xd068eef6;

for (int ihash = 0; ihash<4; ++ihash)
{
    if (p8hash[ihash]==p8[3-ihash])
    {
        pflag = 1;
    }
    else
    {
        pflag = 0;
    }
}

printf("There is a match if flag is 1. Value is = %d", pflag);
    return 0;
}
