//
// Created by 15428 on 8/2/2025.
//

#ifndef MODBUS_PACKET_HPP
#define MODBUS_PACKET_HPP
#include <iostream>
#include <vector>
#include <iomanip>

struct Packet{
    uint8_t byte1; // 从站地址
    uint8_t byte2; // 功能码
    uint8_t byte3; // 数据长度（如果是读取寄存器）
    std::vector<uint8_t> data; // 数据
    uint16_t crc; // 校验
};

// 发送 Modbus 数据包
void sendPacket(const Packet& packet);

#endif //MODBUS_PACKET_HPP
