/// #include <Arduino.h>
#include "IPAddress.h"

#include <cstring>

#include "common/format.hpp"

IPAddress::IPAddress(){
    _address.dword = 0;
}

IPAddress::IPAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet){
    _address.bytes[0] = first_octet;
    _address.bytes[1] = second_octet;
    _address.bytes[2] = third_octet;
    _address.bytes[3] = fourth_octet;
}

IPAddress::IPAddress(uint32_t address){
    _address.dword = address;
}

IPAddress& IPAddress::operator=(uint32_t address){
    _address.dword = address;
    return *this;
}

IPAddress::IPAddress(const uint8_t *address){
    memcpy(_address.bytes, address, sizeof(_address.bytes));
}

IPAddress& IPAddress::operator=(const uint8_t *address){
    memcpy(_address.bytes, address, sizeof(_address.bytes));
    return *this;
}

void IPAddress::print() const
{
	utils::format("%d, %d, %d, %d\n")
		% static_cast<uint32_t>(_address.bytes[0])
		% static_cast<uint32_t>(_address.bytes[1])
		% static_cast<uint32_t>(_address.bytes[2])
		% static_cast<uint32_t>(_address.bytes[3]);
}
