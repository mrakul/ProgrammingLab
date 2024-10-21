#include <stddef.h>
#include <cstring>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
// #include <arpa/inet.h>

static inline uint8_t
count_ones_in_byte(const uint8_t &byte_to_count) {
    static const uint8_t NIBBLE_LOOKUP[16] =
    {
        0, 1, 1, 2, 1, 2, 2, 3,
        1, 2, 2, 3, 2, 3, 3, 4
    };

    return NIBBLE_LOOKUP[byte_to_count & 0x0F] + NIBBLE_LOOKUP[byte_to_count >> 4];
}

static inline double
get_simple_bin_entropy(const uint8_t* data, size_t data_len)
{
    size_t num_of_ones = 0;

    // Get number of bits set in data
    for (size_t cur_byte_num = 0; cur_byte_num < data_len; ++cur_byte_num) {
        num_of_ones += count_ones_in_byte(data[cur_byte_num]);
    }

    // Probability of a set bit occasion in data
    double p = ((double) num_of_ones / (data_len * 8));

    return -(p * log2(p)) - ((1 - p) * log2(1 - p));
}



static inline unsigned
get_dns_name_up_to_level2(char *input_str, unsigned input_len)
{
    size_t cur_domain_level = 1;                                // Considering SNI starts with the 1-st level (no root at the end)
    char   *cur_char = input_str + input_len - 1;               // Start from the end of SNI

    // Move backwards until the beginning of SNI OR until the second domain level passed
    while(cur_char != input_str) {
        if (*cur_char == '.') {
            ++cur_domain_level;
            if (cur_domain_level == 3) {                        // Reached domain level 3
                break;                                          // Stop here
            }
        }
        --cur_char;
    }

    if (cur_char == input_str) {                                // If reached SNI beginning
        if (*cur_char == '.') {                                 // If the left-most symbol is dot at any level
            return input_len - 1;                               // Cut-off dot
        } else {                                                // Otherwise, non-dot symbol
            return input_len;                                   // Return full length
        }
    } else {                                                    // If stopped at level 3 dot
        return input_len - (cur_char - input_str) - 1;          // Return the length of the part up to level 2
    }                                                           // (skip the first level 3 char and dot)
}

/** @return the URI end position if ':' is found. Otherwise, returns 0 */
static inline unsigned
get_uri_hostname(char *str, unsigned len)
{
    // Move forward after "CONNECT " until colon is found within boundaries
    for (unsigned uri_end_pos = 0; uri_end_pos < len; ++uri_end_pos) {
        if (str[uri_end_pos] == ':') {
            return uri_end_pos;
        }
    }

    return 0;
}


/** @return the power of ten depending on the symbol position in an octet */
static inline unsigned
octet_digit_power_of_ten(unsigned digit_position)
{
    switch (digit_position) {
        case 0: return 1;
        case 1: return 10;
        case 2: return 100;
        default: return 0;
    }
}


/** @return uint32_t IPv4 value if the string in IPv4 format. Otherwise, returns 0x00000000.
*** Note:   returned value is in the network byte order */
static inline uint32_t
get_ipv4_from_string(char *input_str, unsigned input_len)
{
    uint32_t ip_in_hex = 0x00000000;                            // Initialize as IP: 0.0.0.0
    uint8_t  cur_octet_hex = 0;                                 // Accumulator for the current octet hex value
    unsigned cur_octet_num = 0;                                 // Starts from the formal 0-th octet from right
    unsigned char_num_in_section = 0;                           // Symbol in a section from the right

    // Move backwards until the beginning of input string OR input is not in IPv4 format
    char *cur_symbol = &input_str[input_len - 1];

    while (cur_symbol != input_str) {
        if (*cur_symbol != '.') {                               // Current symbol is not a separator
            // Symbol is within ASCII digits [0x30;0x39] AND the current octet boundaries
            if ((*cur_symbol >= '0' && *cur_symbol <= '9') && char_num_in_section < 3) {
                cur_octet_hex += (*cur_symbol - '0') * octet_digit_power_of_ten(char_num_in_section);
                ++char_num_in_section;
            } else {                                            // Not a digit symbol OR more than 3 symbols in octet
                return 0;                                       // Stop processing
            }
        }
        // If the current symbol is dot, assign the processed octet value until 4 octets processed
        else {
            ip_in_hex = (ip_in_hex << 8) | cur_octet_hex;       // Save the current octet accordingly
            ++cur_octet_num;                                    // Set the next octet
            cur_octet_hex = 0x00;                               // Reset the current octet value
            char_num_in_section = 0;                            // Reset the current symbol position

            if (cur_octet_num == 4) {                           // Exceeded max number of octets in IPv4
                return 0;                                       // Stop processing
            }
        }

        --cur_symbol;                                           // Check the next in turn symbol
    }

    // If reached the string beginning still having IPv4 format, check the first symbol as a borderline case
    if (*cur_symbol >= '0' && *cur_symbol <= '9' &&
        char_num_in_section < 3) {
            cur_octet_hex += (*cur_symbol - '0') * octet_digit_power_of_ten(char_num_in_section);
            ip_in_hex = (ip_in_hex << 8) | cur_octet_hex;
    } else {
        return 0;
    }

    return ip_in_hex;
}


int main(int argc, char const *argv[])
{
    // 0. get_ipv4_from_string() testing
    char stringIPcandidate[] = "255.8.8.8";
    size_t stringIPlen = strlen(stringIPcandidate);
    uint32_t ip_in_hex = get_ipv4_from_string(stringIPcandidate, stringIPlen);

    // 1. get_uri_hostname() testing
    // unsigned out_len = 0;
    // char *start_pos = nullptr;
    // char uri1[] = "CONNECT xxx.xxx.xxx:2332";
    // size_t uri1Len = strlen(uri1);

    // start_pos = get_uri_hostname(uri1, uri1Len, &out_len);

    // 2. get_dns_name_up_to_level2() testing
    char myString[] = "xxab.cd";
    size_t stringLength = strlen(myString);
    size_t len_up_to_level2 = get_dns_name_up_to_level2(myString, stringLength);

    char myString2[] = "xxx.ab.cd";
    size_t stringLength2 = strlen(myString2);
    len_up_to_level2 = get_dns_name_up_to_level2(myString2, stringLength2);

    char myString3[] = "ab.cd";
    size_t stringLength3 = strlen(myString3);
    len_up_to_level2 = get_dns_name_up_to_level2(myString3, stringLength3);

    char myString7[] = ".ab.cd";
    size_t stringLength7 = strlen(myString7);
    len_up_to_level2 = get_dns_name_up_to_level2(myString7, stringLength7);

    char myString6[] = "x.ab.cd";
    size_t stringLength6 = strlen(myString6);
    len_up_to_level2 = get_dns_name_up_to_level2(myString6, stringLength6);

    char myString4[] = "ru";
    size_t stringLength4 = strlen(myString4);
    len_up_to_level2 = get_dns_name_up_to_level2(myString4, stringLength4);

    char myString5[] = ".ru";
    size_t stringLength5 = strlen(myString5);
    len_up_to_level2 = get_dns_name_up_to_level2(myString5, stringLength5);

    // 3. <arpa/inet.h> testing: inet_pton(), inet_ntop()
    // struct sockaddr_in socket_addr;
    // char ip_in_chars[INET_ADDRSTRLEN];

    // inet_pton(AF_INET, "10.0.0.24", &(socket_addr.sin_addr));
    // inet_ntop(AF_INET, &(socket_addr.sin_addr), ip_in_chars, INET_ADDRSTRLEN);

    // printf("0x%08x\n", *(reinterpret_cast<uint32_t*>(&socket_addr.sin_addr)));
    // printf("%s\n", ip_in_chars);

    return 0;
}