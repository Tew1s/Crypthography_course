#include <iostream>
#include <bitset>
#include <stdlib.h>

const size_t lenBits = 8;
const size_t lenSBox = 16;

//Forward
//input bits : 0 1 2 3 4 5 6 7
//pos bits   : 4 0 7 6 2 3 5 1
const int p_box_rule[lenBits] = {4, 0, 7, 6, 2, 3, 5, 1};

//function to generate p_box_reverse_rule
int* generate_reverse_p_box_rule(const int* arr){
    static int temp[lenBits];
    for(int i = 0; i < lenBits; i++){
        temp[arr[i]] = i;
    }
    return temp;
}
//Backward
int* p_box_reverse_rule = generate_reverse_p_box_rule(p_box_rule);

// AES S-box table
const unsigned char sBox[16][16]={
    {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76},
    {0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0},
    {0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15},
    {0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75},
    {0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84},
    {0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF},
    {0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8},
    {0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2},
    {0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73},
    {0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB},
    {0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79},
    {0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08},
    {0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A},
    {0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E},
    {0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF},
    {0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16}
};

//sbox func
unsigned char sBoxSub(unsigned char input){
    return sBox[((input>>4) & 0x0F)][input & 0x0F];
}
//sbox func reverse;
unsigned char sBoxSubReverse(unsigned char input){
    for(unsigned char i = 0; i < lenSBox; i++)
        for (unsigned char j = 0; j < lenSBox; j++)
            if (sBox[i][j] == input)
                return (i << 4) | j;
    return 0xF;
}

//P-box
unsigned char pBox(unsigned char input){
    unsigned char result = 0;
    for(size_t i = 0; i < lenBits; i++){
        unsigned char bit = (input >> i) & 0x01;
        result |= (bit << p_box_rule[i]);
    }
    return result;
}
//P-box reverse
unsigned char pBoxReverse(unsigned char input){
    unsigned char result= 0;
    for(int i = 0; i < lenBits; i++){
        unsigned char bit = (input >> i) & 0x01;
        result |= (bit << p_box_reverse_rule[i]);
    }   
    return result;
}
unsigned char forwardCipher(unsigned char input){
    return pBox(sBoxSub(input));
}
unsigned char backwardCipher(unsigned char input){
    return sBoxSubReverse(pBoxReverse(input));
}
int main (){

    //For Testing s-box and p-box
    std::cout<<"Testing Forward and Backward block Cipher\n\n"<<std::endl;
    int seed = 300;
    srand (seed);
    for(int i = 0; i < 5; i++){
        unsigned char temp = rand()%256;
        std::cout<<"Input hex num: "<<std::hex<<static_cast<int>(temp)<<std::endl;
        unsigned char temp2 = forwardCipher(temp);
        std::cout<<"Output hex num: "<<std::hex<<static_cast<int>(temp2)<<std::endl;
        std::cout<<"Reverse hex num: "<<std::hex<<static_cast<int>(backwardCipher(temp2))<<"\n"<<std::endl;
        
    }
    std::cout<<"++++++++++++++++++++++++++++++++++++++"<<std::endl;
    //For testing s-box shuffle:
    std::cout<<"\nTesting s-box:\n\n";
    unsigned char input = 0x03;
    std::cout<<"Input hex num: "<<std::hex<<static_cast<int>(input)<<std::endl;
    unsigned char output = sBoxSub(input);
    std::cout<<"Forward S-box: "<<std::hex<<static_cast<int>(output)<<std::endl;
    std::cout<<"Reverse S-box: "<<std::hex<<static_cast<int>(sBoxSubReverse(output))<<std::endl;
    
    std::cout<<"++++++++++++++++++++++++++++++++++++++"<<std::endl;
    //For testing p-box shuffle:
    std::cout<<"\n\n\nTesting p-box:\n\n";
    int num = 1;
    for(int i = 0; i < 8; i++){
        std::cout<<"For element :"<< i + 1<<"\n"<<std::endl;
        std::cout<<"Forward:"<<std::endl;
        std::cout<<"Element "<< i + 1<< " goes to pos: "<<p_box_rule[i] + 1<<std::endl;
        std::bitset<8> input_bin(num);
        std::cout<<"               indx: "<<"87654321"<<std::endl;
        std::cout<<"Input hex num(bin) : "<< input_bin<<std::endl;
        output = pBox(num);
        std::bitset<8> output_bin(output);
        std::cout<<"               indx: "<<"87654321"<<std::endl;
        std::cout<<"Output hex num(bin): "<< output_bin<<std::endl;
        std::cout<<"Backward:"<<std::endl;
        input = pBoxReverse(output);
        std::bitset<8> after_rev(input);
         std::cout<<"Element "<< p_box_rule[i] + 1<< " goes to pos: "<<p_box_reverse_rule[p_box_rule[i]]+1<<std::endl;
        std::cout<<"               indx: "<<"87654321"<<std::endl;
        std::cout<<"After reve num(bin): "<< after_rev<<std::endl;
        std::cout<<"==================================="<<std::endl;
        num *= 2;
    }
    return 0;
}